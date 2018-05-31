#include "ticketprinter.h"

#include <QDir>
#include <QDate>

TicketPrinter::TicketPrinter()
{
}

TicketPrinter::TicketPrinter(TicketWidget *parent)
    :parent(parent)
{
    //listOfPeople
    department = parent->getDepartment();
}

int TicketPrinter::printMealTickets()
{
    QPrinter printer;
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setOrientation(QPrinter::Landscape);
    printer.setResolution(300);
    //TODO choose where to save pdf file
    //QFileDialog opens the file selection popup and returns QString
    QFile pdfFile;
    //---------------------------------
    printer.setOutputFileName(QDir::currentPath().append("/aterialiput.pdf"));
    if(paintImages(printer)) {
        qWarning("Kuvia ei pystytty piirtämään");
        return 1;
    }
    return 0;
}

int TicketPrinter::paintImages(QPrinter &printer)
{
    //TODO cleanup this function. Take "fill rest of the page"-part
    //from the end and make own function for it.
    //Use it to print full page of empty tickets and fill info if needed.
    //ATM this function prints images for each person in listOfPeople,
    //who are attending today. And after that, fills rest of the page with empty images.
    QImage image(QDir::currentPath().append("/lippu_ei_logoa.png"));
    QImage logo(QDir::currentPath().append("/logo.png")); //LOGO

    QPainter painter;
    if(!painter.begin(&printer)) {
        qWarning("Tiedostoa ei pystytty avaamaan.");
        return 1;
    }

    //Pen and font settings
    //Green font color #19A146 (used to print department)
    //Grey font color #6F6F6E (not used at the moment)
    //font Myriad Pro
    QColor departmentColor("#19A146");
    QPen defaultPen;
    QPen departmentPen(departmentColor);
    painter.setFont(QFont("times", 14));

    //Page and image settings
    QRectF pageSize = printer.pageRect();
    QPoint imagePlacement(0.0, 0.0);
    QSizeF imageSizeOnPage(pageSize.width() / wantedImagesOnRow, pageSize.height() / wantedRowsOnPage);
    QRectF imageSourceSize(0.0, 0.0, image.width(), image.height());
    QPoint offset(imageSizeOnPage.width(), 0.0);
    QRectF target(imagePlacement, imageSizeOnPage);

    //Text placement relative to image
    //All placements are relative to the image.
    //The position of the image is changed by moving offset.
    textPlacement = QPointF(imageSizeOnPage.width() / 4, imageSizeOnPage.height() / 1.65);
    QPointF dayPlacement(imageSizeOnPage.width() / 3.1, imageSizeOnPage.height() / 1.38);
    QPointF monthPlacement(imageSizeOnPage.width() / 2.3, imageSizeOnPage.height() / 1.38);
    QPointF yearPlacement(imageSizeOnPage.width() / 1.75, imageSizeOnPage.height() / 1.38);
    QPointF departmentPlacement(imageSizeOnPage.width() / 7.6, imageSizeOnPage.height() / 2.30);
    //QRectF logoPlacement(QPointF(150.0, 20.0), QPointF(600.0, 200.0)); //LOGO

    int dayOfWeek = getDayOfTheWeek();
    QString day = QDate::currentDate().toString("d");
    QString month = QDate::currentDate().toString("M");
    QString year = QDate::currentDate().toString("yyyy");
    int imagesOnRow = 0;
    int rowsOnPage = 0;
    QString department = parent->getDepartment();

    //Print images in 3*4 grid by translating painter by offset(image width on page, 0)
    //After row is full, translate to start of the next row or next page, if the page is full
    foreach(const Person &person, listOfPeople){
        if (isAttendingToday(dayOfWeek, person)) {
            //Translate painter to the new row if current one is full
            if(imagesOnRow >= wantedImagesOnRow){
                painter.translate(-imagesOnRow * imageSizeOnPage.width(), imageSizeOnPage.height());
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
                    painter.resetTransform();
            }
            painter.drawImage(target, image, imageSourceSize);
            //painter.drawImage(logoPlacement, logo.scaled(QSize(), Qt::KeepAspectRatio, Qt::SmoothTransformation), QRectF(0.0, 0.0, logo.width(), logo.height())); //LOGO
            painter.drawImage(logoPlacement, logo, QRectF(0.0, 0.0f, logo.width(), logo.height())); //LOGO
            painter.drawText(textPlacement, person.name);
            painter.drawText(dayPlacement, day);
            painter.drawText(monthPlacement, month);
            painter.drawText(yearPlacement, year);
            painter.setFont(QFont("times", 12));
            painter.setPen(departmentPen);
            painter.drawText(departmentPlacement, department);
            painter.setFont(QFont("times", 14));
            painter.setPen(defaultPen);
            painter.translate(offset); //Move painter to the left by imageWidth
            imagesOnRow++;
        }
    }
    //Fill rest of the page with tickets without name and date
    while (rowsOnPage < wantedRowsOnPage) {
        if(imagesOnRow >= wantedImagesOnRow){
            painter.translate(-imagesOnRow * imageSizeOnPage.width(), imageSizeOnPage.height());
            imagesOnRow = 0;
            rowsOnPage++;
        }
        if(rowsOnPage < wantedRowsOnPage && imagesOnRow < wantedImagesOnRow)
            painter.drawImage(target, image, imageSourceSize);
            painter.drawImage(logoPlacement, logo, QRectF(0.0, 0.0f, logo.width(), logo.height())); //LOGO
            painter.setPen(departmentPen);
            painter.setFont(QFont("Myriad Pro", 12));
            painter.drawText(departmentPlacement, department);
            painter.setFont(QFont("times", 14));
            painter.setPen(defaultPen);
            painter.translate(offset);
            imagesOnRow++;
    }
    painter.end();
    return 0;
}

bool TicketPrinter::isAttendingToday(int DayOfWeek, Person person)
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

int TicketPrinter::getDayOfTheWeek()
{
    QDate date(QDate::currentDate());

    return date.dayOfWeek();
}

void TicketPrinter::setTestPlacement(QRectF placement)
{
    logoPlacement = placement;
}
