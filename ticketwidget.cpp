#include "ticketwidget.h"

#include <QDir>
#include <QPixmap>

TicketWidget::TicketWidget()
{
    QPixmap image(QDir::currentPath().append("/lippu.png"));
    imageLabel = new QLabel(this);
    imageLabel->setPixmap(image);
    mainLayout = new QHBoxLayout(this);
    setLayout(mainLayout);
    mainLayout->addWidget(imageLabel);
}
