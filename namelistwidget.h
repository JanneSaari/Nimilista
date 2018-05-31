#ifndef NAMELISTWIDGET_H
#define NAMELISTWIDGET_H

#include "tablemodel.h"
#include "workstations.h"
#include "person.h"

#include <QItemSelection>
#include <QWidget>
#include <QtWidgets>

class MainWindow;
class QSortFilterProxyModel;

class NamelistWidget : public QWidget
{
    Q_OBJECT

public:
    NamelistWidget(MainWindow *parent = 0);
    ~NamelistWidget();
    TableModel *table;
    Workstations *workstations;
    void readFromFile(const QString &fileName);
    void writeToFile(const QString &fileName);

public slots:
    void showAddEntryDialog();
    void addEntry(Person person);
    void editEntry();
    void removeEntry();

signals:
    void selectionChanged(const QItemSelection &selected);

private:
    void setupNamelist();

    MainWindow *parent;
    QTableView *tableView;

    bool readingFromFile = false; //Used to prevent duplicate error while loading existing list from file.
    bool firstTimeOpening = true; //Prevents error when opening program for the first time.

    QSortFilterProxyModel *proxyModel;
};

#endif // NAMELISTWIDGET_H
