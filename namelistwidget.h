/****************************************************************************
MIT License

Copyright (c) 2018 Janne Saari

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
****************************************************************************/

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
