#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "namelistwidget.h"
#include "ticketwidget.h"

#include <QMainWindow>
#include <QTabWidget>
#include <QDockWidget>
#include <QHBoxLayout>
#include <QPushButton>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow();
    ~MainWindow();

    void setDepartment(QString newDepartment);
    QString getDepartment();

private slots:
    void updateActions(const QItemSelection &selection);
    void openFile();
    void saveFile();

private:
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
    QPushButton *makeTicketsButton;

    //Menu
    QMenu *fileMenu;
    QMenu *toolMenu;
    QMenu *ticketMenu;

    //Actions
    QAction *openAct;
    QAction *saveAct;
    QAction *exitAct;
    QAction *editAct;
    QAction *removeAct;
    QAction *addAct;
    QAction *printAct;
    QAction *openImageAct;

    QString department;
};

#endif // MAINWINDOW_H
