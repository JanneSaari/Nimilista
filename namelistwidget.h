#ifndef NAMELISTWIDGET_H
#define NAMELISTWIDGET_H

#include "newpersontab.h"
#include "tablemodel.h"

#include <QItemSelection>
#include <QTabWidget>

class MainWindow;

class NamelistWidget : public QTabWidget
{
    Q_OBJECT

public:
    NamelistWidget(MainWindow *parent = 0);
    TableModel *table;
    void readFromFile(const QString &fileName);
    void writeToFile(const QString &fileName);

    //Getters
    QVector<int> getFreeMorningWorkstations() const;
    QVector<int> getFreeEveningWorkstations() const;
    int getNumberOfWorkstations() const;
    QString getDepartment() const;
    //Setters
    void setDepartment(QString newDepartment);

public slots:
    void showAddEntryDialog();
    void addEntry(Person person);
    void editEntry();
    void removeEntry();
    void printMealTickets();


signals:
    void selectionChanged(const QItemSelection &selected);

private:
    void setupNamelist();
    QString department;
    MainWindow *parent;
    //Used to prevent duplicate error while loading existing list from file.
    bool readingFromFile = false;

//    NewPersonTab *newPersonTab;
    QSortFilterProxyModel *proxyModel;
};

#endif // NAMELISTWIDGET_H