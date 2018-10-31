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

#include "ticketwidget.h"
#include "ticketprinter.h"

#include <QDir>
#include <QPixmap>
#include <QDate>
#include <QPainter>

TicketWidget::TicketWidget(MainWindow *parent)
    :parent(parent)
{
    ticketImage = QPixmap(QDir::currentPath().append("/lippu_ei_logoa.png"));
    imageLabel = new QLabel(this);
    imageLabel->setPixmap(ticketImage);
    imageLabel->setGeometry(0, 0, ticketImage.width(), ticketImage.height());

    logoImage = QPixmap(QDir::currentPath().append("/logo.png"));
    logoLabel = new MovableLabel(this);
    int logoScaledWidth = 300;
    logoLabel->setPixmap(logoImage.scaledToWidth(logoScaledWidth, Qt::SmoothTransformation));
    logoLabel->setGeometry(0, 0, logoScaledWidth, logoImage.scaledToWidth(logoScaledWidth).height());

//    nameLabel = new MovableLabel(this);
//    nameLabel->setGeometry(200, 150, 300, 250);
//    nameLabel->setText(tr("Esimerkki Nimi"));
//    nameLabel->setFont(QFont("Ariel", 30));

//    dateLabel = new MovableLabel(this);
//    dateLabel->setGeometry(300, 300, 400, 400);
//    dateLabel->setText(QDate::currentDate().toString("dd.MM.yyyy"));
//    dateLabel->setFont(QFont("Ariel", 30));
}

void TicketWidget::printTickets()
{
    QPainter painter;
    painter.begin(&ticket);
    painter.drawPixmap(imageLabel->geometry(), ticketImage, ticketImage.rect());
    painter.drawPixmap(logoLabel->geometry(), logoImage, logoImage.rect());
    painter.end();
    ticket.save("ticket");

    TicketPrinter testi(ticket, this);
    testi.setTestPlacement(logoLabel->geometry());
    testi.printMealTickets();
}

QString TicketWidget::getDepartment() const
{
    return parent->getDepartment();
}

void TicketWidget::setDepartment(QString department)
{
    parent->setDepartment(department);
}
