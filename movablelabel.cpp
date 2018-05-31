#include "movablelabel.h"

MovableLabel::MovableLabel(QWidget *parent)
{
    this->setParent(parent);
    this->setAutoFillBackground(true);
    QPalette pal= this->palette();
    QColor testiColor = QColor(Qt::gray);
    testiColor.setAlpha(50);
    pal.setColor(QPalette::Window, testiColor);
    setPalette(pal);
}

void MovableLabel::mouseMoveEvent(QMouseEvent *event)
{
    if(event->buttons() & Qt::LeftButton)
    {
        this->move(mapToParent(event->pos() - QPoint(0, this->height() / 2)));
        //Need to get and subtrack the offset
        //this->move(mapToParent(event->pos()));
    }
}
