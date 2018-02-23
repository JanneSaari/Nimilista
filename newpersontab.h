//Shows "add new person" tab if the list of people is empty
//Not working currently and not used anywhere
//Delete maybe at some point or fix it

#ifndef NEWPERSONTAB_H
#define NEWPERSONTAB_H

#include <QtWidgets>

#include "tablemodel.h"

class QLabel;
class QPushButton;
class QVBoxLayout;

class NewPersonTab : public QWidget
{
    Q_OBJECT

public:
    NewPersonTab(QWidget *parent = 0);

public slots:
    void addEntry();

signals:
    void sendDetails(Person person);

private:
    QLabel *descriptionLabel;
    QPushButton *addButton;
    QVBoxLayout *mainLayout;
};

#endif // NEWPERSONTAB_H
