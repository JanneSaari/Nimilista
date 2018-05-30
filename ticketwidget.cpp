#include "ticketwidget.h"

#include <QDir>
#include <QPixmap>

TicketWidget::TicketWidget()
{
    QPixmap ticketImage(QDir::currentPath().append("/lippu_ei_logoa.png"));
    imageLabel = new QLabel(this);
    imageLabel->setPixmap(ticketImage);
    imageLabel->setGeometry(0, 0, ticketImage.width(), ticketImage.height());

    QPixmap logoImage(QDir::currentPath().append("/logo.png"));
    logoLabel = new MovableLabel(this);
    logoLabel->setPixmap(logoImage.scaledToWidth(100, Qt::SmoothTransformation));
    logoLabel->setGeometry(0, 0, 560, 560);
    logoLabel->raise();

    nameLabel = new MovableLabel(this);
    nameLabel->setGeometry(200, 150, 500, 500);
    nameLabel->setText(tr("Esimerkki Nimi"));

    dateLabel = new MovableLabel(this);
    dateLabel->setGeometry(300, 300, 600, 600);
}
