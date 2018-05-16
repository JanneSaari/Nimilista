#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "departmentdialog.h"

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
    createButtons();
    setWindowTitle("Nimilista");
    loadSettings();
    if(department == NULL)
        openDepartmentDialog();
}

MainWindow::~MainWindow()
{
    saveSettings();
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
    printAct = new QAction(tr("&Piirrä aterialiput"), this);

    ticketMenu->addAction(printAct);
    connect(printAct, &QAction::triggered, namelistWidget, &NamelistWidget::printMealTickets);

    QAction* setDepartmentAction = ticketMenu->addAction(tr("Aseta paja"));
    connect(setDepartmentAction, &QAction::triggered, this, &MainWindow::openDepartmentDialog);
}

void MainWindow::createButtons()
{
    bottomDockWidget = new QDockWidget(this, Qt::Widget);
    bottomDockWidget->setAllowedAreas(Qt::BottomDockWidgetArea);
    addDockWidget(Qt::BottomDockWidgetArea, bottomDockWidget);
    bottomDockWidget->setFeatures(QDockWidget::NoDockWidgetFeatures);

    buttonWidget = new QWidget(this);
    buttonLayout = new QHBoxLayout(buttonWidget);
    bottomDockWidget->setWidget(buttonWidget);
    buttonWidget->setLayout(buttonLayout);

    addPersonButton = new QPushButton(tr("Lisää"), this);
    buttonLayout->addWidget(addPersonButton);
    connect(addPersonButton, QPushButton::clicked, namelistWidget, &NamelistWidget::showAddEntryDialog);

    editPersonButton = new QPushButton(tr("Muokkaa"), this);
    editPersonButton->setEnabled(false);
    buttonLayout->addWidget(editPersonButton);
    connect(editPersonButton, QPushButton::clicked, namelistWidget, &NamelistWidget::editEntry);

    removePersonButton = new QPushButton(tr("Poista"), this);
    removePersonButton->setEnabled(false);
    buttonLayout->addWidget(removePersonButton);
    connect(removePersonButton, QPushButton::clicked, namelistWidget, &NamelistWidget::removeEntry);

    makeTicketsButton = new QPushButton(tr("Piirrä aterialiput"), this);
    buttonLayout->addWidget(makeTicketsButton);
    connect(makeTicketsButton, QPushButton::clicked, namelistWidget, &NamelistWidget::printMealTickets);
}

void MainWindow::updateActions(const QItemSelection &selection)
{
    QModelIndexList indexes = selection.indexes();

    if(!indexes.isEmpty()){
        removeAct->setEnabled(true);
        editAct->setEnabled(true);
        editPersonButton->setEnabled(true);
        removePersonButton->setEnabled(true);
    } else {
        removeAct->setEnabled(false);
        editAct->setEnabled(false);
        editPersonButton->setEnabled(false);
        removePersonButton->setEnabled(false);
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

void MainWindow::saveSettings()
{
    QFile settingsFile("settings");
    if(!settingsFile.open(QIODevice::WriteOnly)) {
        //ERROR here if needed
        return;
    }
    QDataStream out(&settingsFile);
    out << department;
}

void MainWindow::loadSettings()
{
    QFile settingsFile("settings");
    if(!settingsFile.open(QIODevice::ReadOnly)) {
        //ERROR
        return;
    }
    QDataStream in(&settingsFile);
    in >> department;
}

void MainWindow::openDepartmentDialog()
{
    DepartmentDialog departmentDialog(this);

    if(departmentDialog.exec()) {
        setDepartment(departmentDialog.departmentName->text());
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
