#include "mealtickets.h"
#include "namelistwidget.h"

#include <QDir>
#include <QDate>

MealTickets::MealTickets()
{
}

MealTickets::MealTickets(NamelistWidget *parent)
    :parent(parent)
{
    listOfPeople = parent->table->getPeople();
    department = parent->getDepartment();
}

int MealTickets::printMealTickets()
{
    QPrinter printer;
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setOrientation(QPrinter::Landscape);
    printer.setResolution(300);
    //TODO choose where to save pdf file
    //QFileDialog opens the file selection popup adn returns QString
    QFile pdfFile;
    //---------------------------------
    printer.setOutputFileName(QDir::currentPath().append("/aterialiput.pdf"));
    if(paintImages(printer)) {
        qWarning("Kuvia ei pystytty piirtämään");
        return 1;
    }
    return 0;
}

int MealTickets::paintImages(QPrinter &printer)
{
    //TODO cleanup this function. Take "fill rest of the page"-part
    //from the end and make own function for it.
    //Use it to print full page of empty tickets and fill info if needed.
    //ATM this function prints images for each person in listOfPeople,
    //who are attending today. And after that, fills rest of the page with empty images.

    //Logo printing is commented out and indicated by //LOGO comment

    //Logon piirtäminen on kommentoitu pois ja merkitty kommentilla //LOGO
    //Logon piirtämisen PITÄISI toimia, kun kaikki //LOGO merkityt kohdat on otettu pois kommenteista.
    QImage image(QDir::currentPath().append("/lippu.png"));
    //QImage logo(QDir::currentPath().append(/logo.png)); //LOGO


    QPainter painter;
    if(!painter.begin(&printer)) {
        qWarning("Tiedostoa ei pystytty avaamaan.");
        return 1;
    }

    //Green font color #19A146 (used to print department)
    //Grey font color #6F6F6E (not used at the moment)
    //font Myriad Pro
    QColor testiColor("#19A146");
    QPen defaultPen;
    QPen testiPen(testiColor);

    QRectF pageSize = printer.pageRect();
    QPoint imagePlacement(0.0, 0.0);
    QSizeF imageSizeOnPage(pageSize.width() / 3, pageSize.height() / 4);
    QRectF imageSourceSize(0.0, 0.0, image.width(), image.height());
    QPoint offset(imageSizeOnPage.width(), 0.0);
    QRectF target(imagePlacement, imageSizeOnPage);
    painter.setFont(QFont("times", 14));

    //Text placement relative to image
    QPointF textPlacement(imageSizeOnPage.width() / 4, imageSizeOnPage.height() / 1.65);
    QPointF dayPlacement(imageSizeOnPage.width() / 3.1, imageSizeOnPage.height() / 1.38);
    QPointF monthPlacement(imageSizeOnPage.width() / 2.3, imageSizeOnPage.height() / 1.38);
    QPointF yearPlacement(imageSizeOnPage.width() / 1.75, imageSizeOnPage.height() / 1.38);
    QPointF PajaPlacement(imageSizeOnPage.width() / 7.6, imageSizeOnPage.height() / 2.30);
    //Vaihda sopivaan kohtaan suhteessa lippuun.
    //Argumentit ovat vasen ylänurkka ja oikea alanurkka
    //QRectF logoPlacement(0.0, 0.0); //LOGO
    int dayOfWeek = getDayOfTheWeek();

    int imagesOnRow = 0;
    int rowsOnPage = 0;
    QString department = parent->getDepartment();

    //Print images in 3*4 grid by translating painter by offset(image width on page, 0)
    //After row is full, translate to start of the next row or next page, if the page is full
    foreach(const Person &person, listOfPeople){
        if (isAttendingToday(dayOfWeek, person)) {
            //Translate painter to the new row if current one is full
            if(imagesOnRow >= 3){
                painter.translate(-imagesOnRow * imageSizeOnPage.width(), imageSizeOnPage.height());
                imagesOnRow = 0;
                rowsOnPage++;
            }
            //Translate painter to the new page if current one is full
            if(rowsOnPage >= 4) {
                    if(! printer.newPage()) {
                        qWarning("Uuden sivun tekeminen ei onnistunut.");
                        return 1;
                    }
                    rowsOnPage = 0;
                    painter.resetTransform();
            }
            painter.drawImage(target, image, imageSourceSize);
            //painter.drawImage(logoPlacement, logo, logo.size()); //LOGO
            painter.drawText(textPlacement, person.name);
            painter.drawText(dayPlacement, QDate::currentDate().toString("d"));
            painter.drawText(monthPlacement, QDate::currentDate().toString("M"));
            painter.drawText(yearPlacement, QDate::currentDate().toString("yyyy"));
            painter.setFont(QFont("times", 12));
            painter.setPen(testiPen);
            painter.drawText(PajaPlacement, department);
            painter.setFont(QFont("times", 14));
            painter.setPen(defaultPen);
            painter.translate(offset); //Move painter to the left by imageWidth
            imagesOnRow++;
        }
    }
    while (rowsOnPage < 4) {
        if(imagesOnRow >= 3){
            painter.translate(-imagesOnRow * imageSizeOnPage.width(), imageSizeOnPage.height());
            imagesOnRow = 0;
            rowsOnPage++;
        }
        if(rowsOnPage <4 &&imagesOnRow < 3)
            painter.drawImage(target, image, imageSourceSize);
            //painter.drawImage(logoPlacement, logo, logo.size()); //LOGO
            painter.setPen(testiPen);
            painter.setFont(QFont("Myriad Pro", 12));
            painter.drawText(PajaPlacement, department);
            painter.setFont(QFont("times", 14));
            painter.setPen(defaultPen);
            painter.translate(offset);
            imagesOnRow++;
    }
    painter.end();
    return 0;
}

bool MealTickets::isAttendingToday(int DayOfWeek, Person person)
{
    switch (DayOfWeek) {
    case 1:
        return person.isMonday;
        break;
    case 2:
        return person.isTuesday;
        break;
    case 3:
        return person.isWednesday;
        break;
    case 4:
        return person.isThursday;
        break;
    case 5:
        return person.isFriday;
        break;
    default:
        return false;
        break;
    }
}

int MealTickets::getDayOfTheWeek()
{
    QDate date(QDate::currentDate());

    return date.dayOfWeek();
}
