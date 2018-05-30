#ifndef TICKETWIDGET_H
#define TICKETWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QHBoxLayout>

class TicketWidget : public QWidget
{
public:
    TicketWidget();

private:
    QLabel *imageLabel;
    QHBoxLayout *mainLayout;
};

#endif // TICKETWIDGET_H
