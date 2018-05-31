#include "ticketwidget.h"

#include <QDir>
#include <QPixmap>
#include <QDate>

TicketWidget::TicketWidget()
{
    QPixmap ticketImage(QDir::currentPath().append("/lippu_ei_logoa.png"));
    imageLabel = new QLabel(this);
    imageLabel->setPixmap(ticketImage);
    imageLabel->setGeometry(0, 0, ticketImage.width(), ticketImage.height());

    QPixmap logoImage(QDir::currentPath().append("/logo.png"));
    logoLabel = new MovableLabel(this);
    logoLabel->setPixmap(logoImage.scaledToWidth(300, Qt::SmoothTransformation));
    logoLabel->setGeometry(0, 0, 560, 200);

    nameLabel = new MovableLabel(this);
    nameLabel->setGeometry(200, 150, 300, 250);
    nameLabel->setText(tr("Esimerkki Nimi"));
    nameLabel->setFont(QFont("Ariel", 30));

    dateLabel = new MovableLabel(this);
    dateLabel->setGeometry(300, 300, 400, 400);
    dateLabel->setText(QDate::currentDate().toString("dd.MM.yyyy"));
    dateLabel->setFont(QFont("Ariel", 30));
}
