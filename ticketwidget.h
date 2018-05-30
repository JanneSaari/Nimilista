#ifndef TICKETWIDGET_H
#define TICKETWIDGET_H

#include "movablelabel.h"

#include <QWidget>
#include <QVector>
#include <QLabel>

class TicketWidget : public QWidget
{
public:
    TicketWidget();

private:
    QLabel *imageLabel;
    MovableLabel *logoLabel;
    MovableLabel *nameLabel;
    MovableLabel *dateLabel;

    //Not sure if needed yet
    //QVector<MovableLabel> customLabels;
};

#endif // TICKETWIDGET_H
