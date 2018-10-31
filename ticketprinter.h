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

#ifndef MEALTICKETS_H
#define MEALTICKETS_H

#include <QPainter>
#include <QPrinter>
#include <QPicture>

#include <person.h>
#include "ticketwidget.h"

//Handles printing list of tickets to PDF file.
//Adds names of the people who are attending that day
//and date to pre-definet positions.

class TicketPrinter
{
public:
    TicketPrinter(QPicture ticket, TicketWidget *parent = nullptr);
    int printMealTickets();

    //set placement testi
    void setTestPlacement(QRectF placement);

private:
    QPicture ticket;
    TicketWidget *parent;
    QPrinter *printer;
    QPainter *painter;
    QList<Person> listOfPeople;
    QString department;

    int wantedImagesOnRow = 3;
    int wantedRowsOnPage = 4;
    QPointF textPlacement;
    QRectF logoPlacement;

    int paintImages(QPrinter &printer);
    int getDayOfTheWeek();
    int getCurrentDate();
    bool isAttendingToday(int dayOfWeek, Person person);
};

#endif // MEALTICKETS_H
