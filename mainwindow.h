#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "namelistwidget.h"

#include <QMainWindow>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow();

    void setDepartment(QString newDepartment);
    QString getDepartment();

private slots:
    void updateActions(const QItemSelection &selection);
    void openFile();
    void saveFile();

private:
    void createMenus();

    QString department;

    NamelistWidget *namelistWidget;
    QMenu *fileMenu;
    QMenu *toolMenu;
    QAction *openAct;
    QAction *saveAct;
    QAction *exitAct;
    QAction *editAct;
    QAction *removeAct;
    QAction *addAct;

    QMenu *ticketMenu;
    QAction *printAct;
    QAction *openImageAct;
};

#endif // MAINWINDOW_H
