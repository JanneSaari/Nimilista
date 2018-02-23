#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QAction>
#include <QFileDialog>
#include <QMenuBar>
#include <functional>

MainWindow::MainWindow()
{
    resize(1200, 800);
    namelistWidget = new NamelistWidget(this);
    setCentralWidget(namelistWidget);
    createMenus();
    setWindowTitle("Nimilista");
}

void MainWindow::createMenus()
{
    fileMenu = menuBar()->addMenu(tr("&Tiedosto")); //tr() can be used to add translations

    openAct = new QAction(tr("&Avaa..."), this);
    fileMenu->addAction(openAct);
    connect(openAct, &QAction::triggered, this, &MainWindow::openFile);

    saveAct = new QAction(tr("&Tallenna..."), this);
    fileMenu->addAction(saveAct);
    connect(saveAct, &QAction::triggered, this, &MainWindow::saveFile);

    fileMenu->addSeparator();

    exitAct = new QAction(tr("&Sulje..."), this);
    fileMenu->addAction(exitAct);
    connect(exitAct, &QAction::triggered, this, &QWidget::close);

    toolMenu = menuBar()->addMenu(tr("&Työkalut"));

    addAct = new QAction(tr("&Lisää Henkilö..."), this);
    toolMenu->addAction(addAct);
    connect(addAct, &QAction::triggered, namelistWidget, &NamelistWidget::showAddEntryDialog);

    editAct = new QAction(tr("&Muokkaa Henkilöä..."), this);
    editAct->setEnabled(false);
    toolMenu->addAction(editAct);
    connect(editAct, &QAction::triggered, namelistWidget, &NamelistWidget::editEntry);

    toolMenu->addSeparator();

    removeAct = new QAction(tr("&Poista Henkilö..."), this);
    removeAct->setEnabled(false);
    toolMenu->addAction(removeAct);
    connect(removeAct, &QAction::triggered, namelistWidget, &NamelistWidget::removeEntry);

    connect(namelistWidget, &NamelistWidget::selectionChanged, this, &MainWindow::updateActions);

    ticketMenu = menuBar()->addMenu(tr("&Aterialiput"));
    printAct = new QAction(tr("&Tee PDF"), this);

    ticketMenu->addAction(printAct);


    QActionGroup* departmentGroup = new QActionGroup(this);
    QMenu* testiMenu = ticketMenu->addMenu(tr("Pajan valinta"));
    QAction* ITPajaAction = testiMenu->addAction(tr("IT-paja"));
    QAction* MediaPajaAction = testiMenu->addAction(tr("Mediapaja"));
    QAction* MetalliPajaAction = testiMenu->addAction(tr("Metalli- ja kiinteistönhuoltopaja"));
    QAction* PuuPajaAction = testiMenu->addAction(tr("Puu- ja entisöintipaja"));
    QAction* HoivaPajaAction = testiMenu->addAction(tr("Hoivapaja"));

    ITPajaAction->setCheckable(true);
    ITPajaAction->setActionGroup(departmentGroup);
    MediaPajaAction->setCheckable(true);
    MediaPajaAction->setActionGroup(departmentGroup);
    MetalliPajaAction->setCheckable(true);
    MetalliPajaAction->setActionGroup(departmentGroup);
    PuuPajaAction->setCheckable(true);
    PuuPajaAction->setActionGroup(departmentGroup);
    HoivaPajaAction->setCheckable(true);
    HoivaPajaAction->setActionGroup(departmentGroup);

    //Have to use lambda function to bind function with arguments to action.
    //There may be better way, but this works for now.
    //Look for the way to bind namelistWdiget->setDepartment()
    //instead of passing the QString around
    connect(ITPajaAction, &QAction::triggered, [this]()
    {
        setDepartment("IT-paja");
    });
    connect(MediaPajaAction, &QAction::triggered, [this]()
    {
        setDepartment("Mediapaja");
    });
    connect(MetalliPajaAction, &QAction::triggered, [this]()
    {
        setDepartment("Metalli- ja kiinteistönhuoltopaja");
    });
    connect(PuuPajaAction, &QAction::triggered, [this]()
    {
        setDepartment("Puu- ja entisöintipaja");
    });
    connect(HoivaPajaAction, &QAction::triggered, [this]()
    {
        setDepartment("Hoivapaja");
    });

    connect(printAct, &QAction::triggered, namelistWidget, &NamelistWidget::printMealTickets);
}

void MainWindow::updateActions(const QItemSelection &selection)
{
    QModelIndexList indexes = selection.indexes();

    if(!indexes.isEmpty()){
        removeAct->setEnabled(true);
        editAct->setEnabled(true);
    } else {
        removeAct->setEnabled(false);
        editAct->setEnabled(false);
    }
}

void MainWindow::openFile()
{
    QString filename = QFileDialog::getOpenFileName(this);
    if(!filename.isEmpty()) {
        namelistWidget->readFromFile(filename);
    }
}

void MainWindow::saveFile()
{
    QString filename = QFileDialog::getSaveFileName(this);
    if(!filename.isEmpty()) {
        namelistWidget->writeToFile(filename);
    }
}

void MainWindow::setDepartment(QString newDepartment)
{
    department = newDepartment;
}

QString MainWindow::getDepartment()
{
    return department;
}
