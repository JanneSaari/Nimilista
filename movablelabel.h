#ifndef MOVABLELABEL_H
#define MOVABLELABEL_H

#include <QLabel>
#include <QMouseEvent>

//Custom label that can be moved with mouse.
//Used to position text and images on ticket
class MovableLabel : public QLabel
{
public:
    MovableLabel(QWidget *parent = Q_NULLPTR);

    void mouseMoveEvent(QMouseEvent *ev);
private:

};

#endif // MOVABLELABEL_H
