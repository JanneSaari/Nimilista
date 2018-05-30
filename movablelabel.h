#ifndef MOVABLELABEL_H
#define MOVABLELABEL_H

#include <QLabel>
#include <QMouseEvent>

class MovableLabel : public QLabel
{
public:
    MovableLabel(QWidget *parent = Q_NULLPTR);

    void mouseMoveEvent(QMouseEvent *ev);
private:

};

#endif // MOVABLELABEL_H
