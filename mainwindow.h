#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "namelistwidget.h"
#include "ticketwidget.h"
#include "person.h"

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

    QActionGroup *shiftGroup;
    QAction *allShiftsAction;
    QAction *morningShiftAction;
    QAction *dayShiftAction;
    QAction *eveningShiftAction;

    QString department;
};

#endif // MAINWINDOW_H
