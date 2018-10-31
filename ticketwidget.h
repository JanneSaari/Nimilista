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

#ifndef TICKETWIDGET_H
#define TICKETWIDGET_H

#include "movablelabel.h"
#include "mainwindow.h"
#include "person.h"

#include <QWidget>
#include <QVector>
#include <QLabel>
#include <QPicture>
#include <QPixmap>

class TicketWidget : public QWidget
{
public:
    TicketWidget(MainWindow *parent = Q_NULLPTR);

    void setDepartment(QString newDepartment);
    QString getDepartment() const;

    MainWindow *parent;

public slots:
    void printTickets();

private:
    QPicture ticket;
    QLabel *imageLabel;
    QPixmap ticketImage;
    QPixmap logoImage;

    MovableLabel *logoLabel;
    MovableLabel *nameLabel;
    MovableLabel *dateLabel;

    //Not sure if needed yet
    //QVector<MovableLabel> customLabels;
};

#endif // TICKETWIDGET_H
