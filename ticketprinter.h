//Handles printing list of tickets to PDF file.
//Adds names of the people who are attending that day
//and date to pre-definet positions.

#ifndef MEALTICKETS_H
#define MEALTICKETS_H

#include <QPainter>
#include <QPrinter>

#include <person.h>
#include "ticketwidget.h"

class TicketPrinter
{
public:
    TicketPrinter();
    TicketPrinter(TicketWidget *parent = 0);
    int printMealTickets();

    //set placement testi
    void setTestPlacement(QRectF placement);

private:
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
