//Handles printing list of tickets to PDF file.
//Adds names of the people who are attending that day
//and date to pre-definet positions

#ifndef MEALTICKETS_H
#define MEALTICKETS_H

#include <QPainter>
#include <QPrinter>

#include <person.h>
#include "namelistwidget.h"

class MealTickets
{
public:
    MealTickets();
    MealTickets(NamelistWidget *parent = 0);
    int printMealTickets();

private:
    NamelistWidget *parent;
    QPrinter *printer;
    QPainter *painter;
    QList<Person> listOfPeople;
    QString department;

    int paintImages(QPrinter &printer);
    int getDayOfTheWeek();
    int getCurrentDate();
    bool isAttendingToday(int dayOfWeek, Person person);
};

#endif // MEALTICKETS_H
