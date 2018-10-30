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

enum Shifts
{
    ALL_SHIFTS,
    MORNING_SHIFT,
    DAY_SHIFT,
    EVENING_SHIFT
};


class NamelistWidget : public QWidget
{
    Q_OBJECT

public:
    NamelistWidget(MainWindow *parent = nullptr);
    ~NamelistWidget();
    TableModel *table;
    Workstations *workstations;
    Shifts shownShifts = ALL_SHIFTS;

    void readFromFile(const QString &fileName);
    void writeToFile(const QString &fileName);

public slots:
    void showAddEntryDialog();
    void addEntry(Person person);
    void editEntry();
    void removeEntry();
    void changeShownShifts();

signals:
    void selectionChanged(const QItemSelection &selected);

private:
    void setupNamelist();

    MainWindow *parent;
    QTableView *tableView;
    QSortFilterProxyModel *proxyModel;


    bool readingFromFile = false; //Used to prevent duplicate error while loading existing list from file.
    bool firstTimeOpening = true; //Prevents error when opening program for the first time.

};

#endif // NAMELISTWIDGET_H
