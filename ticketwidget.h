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

    void printMealTickets();
    void setDepartment(QString newDepartment);
    QString getDepartment() const;

    MainWindow *parent;

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
