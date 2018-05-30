#include "movablelabel.h"

MovableLabel::MovableLabel(QWidget *parent)
{
    this->setParent(parent);
}

void MovableLabel::mouseMoveEvent(QMouseEvent *event)
{
    if(event->buttons() & Qt::LeftButton)
    {
        //this->move(mapToParent(event->pos() - offset));
        this->move(mapToParent(event->pos()));
    }
}
