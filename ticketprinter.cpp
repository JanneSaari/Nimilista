/****************************************************************************
MIT License

Copyright (c) 2018 Janne Saari

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
****************************************************************************/

#include "ticketprinter.h"

#include <QDir>
#include <QDate>

TicketPrinter::TicketPrinter(QPicture ticket, TicketWidget *parent)
    :ticket(ticket), parent(parent)
{
    painter = new QPainter();
    listOfPeople = parent->parent->getPeople();
    department = parent->getDepartment();
}

TicketPrinter::~TicketPrinter()
{
    delete(painter);
}

int TicketPrinter::printMealTickets()
{
    QPrinter printer;
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setOrientation(QPrinter::Landscape);
    printer.setResolution(300);
    printer.setOutputFileName(QDir::currentPath().append("/aterialiput.pdf"));
    if(paintImages(printer)) {
        qWarning("Kuvia ei pystytty piirtämään");
        return 1;
    }
    return 0;
}

int TicketPrinter::paintImages(QPrinter &printer)
{
    //This function prints images for each person in listOfPeople,
    //who are attending today. And after that, fills rest of the page with empty images.
    image = QImage(QDir::currentPath().append("/lippu.png"));
    //QImage logo(QDir::currentPath().append("/logo.png"));

    if(!painter->begin(&printer)) {
        qWarning("Tiedostoa ei pystytty avaamaan.");
        return 1;
    }

    //Pen and font settings
    //Green font color #19A146 (used to print department)
    //Grey font color #6F6F6E (not used at the moment)
    //font Myriad Pro
    QColor departmentColor("#19A146");
    departmentPen = QPen(departmentColor);
    painter->setFont(QFont("times", 14));

    //Page and image settings
    pageSize = printer.pageRect();
    //QRectF pageRect = pageSize.rectPixels(300);
    imageSizeOnPage = QSizeF(pageSize.width() / wantedImagesOnRow, pageSize.height() / wantedRowsOnPage);
    imageSourceSize = QRectF(0.0, 0.0, image.width(), image.height());
    offset = QPointF(imageSizeOnPage.width(), 0.0);

    //Text placement relative to image.
    //All placements are relative to the image.
    //The position of the image is changed by translating painter by offset.
    imagePlacement = QRectF(QPointF(0.0, 0.0), imageSizeOnPage);
    textPlacement = QPointF(imageSizeOnPage.width() / 4, imageSizeOnPage.height() / 1.65);
    dayPlacement = QPointF(imageSizeOnPage.width() / 3.1, imageSizeOnPage.height() / 1.38);
    monthPlacement = QPointF(imageSizeOnPage.width() / 2.3, imageSizeOnPage.height() / 1.38);
    yearPlacement = QPointF(imageSizeOnPage.width() / 1.75, imageSizeOnPage.height() / 1.38);
    departmentPlacement = QPointF(imageSizeOnPage.width() / 7.6, imageSizeOnPage.height() / 2.30);
    //QRectF logoPlacement(QPointF(150.0, 20.0), QPointF(600.0, 200.0));

    int dayOfWeek = getDayOfTheWeek();
    QString day = QDate::currentDate().toString("d");
    QString month = QDate::currentDate().toString("M");
    QString year = QDate::currentDate().toString("yyyy");
    QString department = parent->getDepartment();

    //TODO change this to QPicture. Try to get QPicture from ticket tab, then just add name and date if needed.
    //Setting QPicture in ticketTab is not working correctly at the moment. I don't have time to get it working. The code is commented out in program.
    //At the moment setting text position is hard coded in, so this would make using different tickets easier.

    //Print images in 3*4 grid by translating painter by offset(QPointF(image width on page, 0))
    //After row is full, translate to start of the next row or next page, if the page is full
    //painter.scale(qreal(imageSizeOnPage.width() / ticket.width()), qreal(imageSizeOnPage.height() / ticket.height()));
    foreach(const Person &person, listOfPeople){
        if (isAttendingToday(dayOfWeek, person)) {
            //Translate painter to the new row if current one is full
            if(imagesOnRow >= wantedImagesOnRow){
                painter->translate(-imagesOnRow * imageSizeOnPage.width(), imageSizeOnPage.height());
                imagesOnRow = 0;
                rowsOnPage++;
            }
            //Translate painter to the new page if current one is full
            if(rowsOnPage >= wantedRowsOnPage) {
                    if(! printer.newPage()) {
                        qWarning("Uuden sivun tekeminen ei onnistunut.");
                        return 1;
                    }
                    rowsOnPage = 0;
                    painter->resetTransform();
            }
            //painter.drawPicture(0, 0, ticket);
            painter->drawImage(imagePlacement, image, imageSourceSize);
            //painter.drawImage(logoPlacement, logo, QRectF(0.0, 0.0f, logo.width(), logo.height()));
            painter->drawText(textPlacement, person.name);
            painter->drawText(dayPlacement, day);
            painter->drawText(monthPlacement, month);
            painter->drawText(yearPlacement, year);
            painter->setFont(QFont("times", 12));
            painter->setPen(departmentPen);
            painter->drawText(departmentPlacement, department);
            painter->setFont(QFont("times", 14));
            painter->setPen(defaultPen);
            painter->translate(offset); //Move painter to the right by width of one ticket on page
            imagesOnRow++;
        }
    }

    if(parent->fillPageWithEmptyTickets){
        fillPage();
    }

    painter->end();

    return 0;
}

void TicketPrinter::fillPage()
{
    //Fill rest of the page with tickets without name and date
    while (rowsOnPage < wantedRowsOnPage) {
        if(imagesOnRow >= wantedImagesOnRow){
            painter->translate(-imagesOnRow * imageSizeOnPage.width(), imageSizeOnPage.height());
            imagesOnRow = 0;
            rowsOnPage++;
        }
        if(rowsOnPage < wantedRowsOnPage && imagesOnRow < wantedImagesOnRow)
            painter->drawImage(imagePlacement, image, imageSourceSize);
            //painter.drawImage(logoPlacement, logo, QRectF(0.0, 0.0f, logo.width(), logo.height()));
            painter->setPen(departmentPen);
            painter->setFont(QFont("Myriad Pro", 12));
            painter->drawText(departmentPlacement, department);
            painter->setFont(QFont("times", 14));
            painter->setPen(defaultPen);
            painter->translate(offset);
            imagesOnRow++;
    }
}

bool TicketPrinter::isAttendingToday(int DayOfWeek, Person person)
{
    //This could be moved to the namelistWidget and just send array of strings instead
    switch (DayOfWeek) {
    case 1:
        return person.isMonday;
    case 2:
        return person.isTuesday;
    case 3:
        return person.isWednesday;
    case 4:
        return person.isThursday;
    case 5:
        return person.isFriday;
    default:
        return false;
    }
}

int TicketPrinter::getDayOfTheWeek()
{
    QDate date(QDate::currentDate());

    return date.dayOfWeek();
}

void TicketPrinter::setPlacement(QRectF placement)
{
    logoPlacement = placement;
}
