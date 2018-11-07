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

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "namelistwidget.h"
#include "ticketwidget.h"

#include <QMainWindow>
#include <QTabWidget>
#include <QDockWidget>
#include <QHBoxLayout>
#include <QPushButton>
#include <QActionGroup>

class TicketWidget;

class MainWindow : public QMainWindow
{
    Q_OBJECT


public:
    MainWindow();
    ~MainWindow();

    void setDepartment(QString newDepartment);
    QList<Person> getPeople();
    QString getDepartment();

private slots:
    void updateActions(const QItemSelection &selection);
    void openFile();
    void saveFile();

private:
    void createActions();
    void createMenus();
    void createButtons();
    void createTabs();
    void saveSettings();
    void loadSettings();
    void openDepartmentDialog();

    QTabWidget *mainWidget;
    NamelistWidget *namelistWidget;
    TicketWidget *ticketWidget;

    //Buttons
    QDockWidget *bottomDockWidget;
    QWidget *buttonWidget;
    QHBoxLayout *buttonLayout;
    QPushButton *addPersonButton;
    QPushButton *editPersonButton;
    QPushButton *removePersonButton;
    QPushButton *drawTicketsButton;

    //Menu
    QMenu *fileMenu;
    QMenu *toolMenu;
    QMenu *ticketMenu;
    QMenu *shiftMenu;

    //Actions
    QAction *openAct;
    QAction *saveAct;
    QAction *exitAct;
    QAction *editAct;
    QAction *removeAct;
    QAction *addAct;
    QAction *printAct;
    QAction *setDepartmentAction;
    QAction *openImageAct;
    QAction *printTableAct;

    QActionGroup *shiftGroup;
    QAction *allShiftsAction;
    QAction *morningShiftAction;
    QAction *dayShiftAction;
    QAction *eveningShiftAction;

    QString department;
};

#endif // MAINWINDOW_H
