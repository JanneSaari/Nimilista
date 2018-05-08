#ifndef NAMELISTWIDGET_H
#define NAMELISTWIDGET_H

#include "tablemodel.h"
#include "workstations.h"
#include "person.h"

#include <QItemSelection>
#include <QTabWidget>

class MainWindow;
class QSortFilterProxyModel;

class NamelistWidget : public QTabWidget
{
    Q_OBJECT

public:
    NamelistWidget(MainWindow *parent = 0);
    ~NamelistWidget();
    TableModel *table;
    Workstations *workstations;
    void readFromFile(const QString &fileName);
    void writeToFile(const QString &fileName);

    QString getDepartment() const;
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

    QSortFilterProxyModel *proxyModel;
};

#endif // NAMELISTWIDGET_H
