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
    mainWidget = new QTabWidget(this);
    createTabs();
    createActions();
    createMenus();
    createButtons();
    setWindowTitle("Nimilista");
    loadSettings();
    if(department.isEmpty())
        openDepartmentDialog();
}

MainWindow::~MainWindow()
{
    saveSettings();
}

void MainWindow::createActions()
{
    openAct = new QAction(tr("&Avaa..."), this);
    connect(openAct, &QAction::triggered, this, &MainWindow::openFile);

    saveAct = new QAction(tr("&Tallenna..."), this);
    connect(saveAct, &QAction::triggered, this, &MainWindow::saveFile);

    exitAct = new QAction(tr("&Sulje..."), this);
    connect(exitAct, &QAction::triggered, this, &QWidget::close);

    addAct = new QAction(tr("&Lisää Henkilö..."), this);
    connect(addAct, &QAction::triggered, namelistWidget, &NamelistWidget::showAddEntryDialog);

    editAct = new QAction(tr("&Muokkaa Henkilöä..."), this);
    editAct->setEnabled(false);
    connect(editAct, &QAction::triggered, namelistWidget, &NamelistWidget::editEntry);

    removeAct = new QAction(tr("&Poista Henkilö..."), this);
    removeAct->setEnabled(false);
    connect(removeAct, &QAction::triggered, namelistWidget, &NamelistWidget::removeEntry);

    printAct = new QAction(tr("&Piirrä aterialiput"), this);
    connect(printAct, &QAction::triggered, ticketWidget, &TicketWidget::printTickets);

    setDepartmentAction = new QAction(tr("&Aseta paja"), this);
    connect(setDepartmentAction, &QAction::triggered, this, &MainWindow::openDepartmentDialog);

    allShiftsAction = new QAction(tr("&Kaikki vuorot"), this);
    morningShiftAction = new QAction(tr("&Aamuvuoro"), this);
    dayShiftAction = new QAction(tr("&Päivävuoro"), this);
    eveningShiftAction = new QAction(tr("&Iltavuoro"), this);

    connect(allShiftsAction, &QAction::triggered, [this](){
        namelistWidget->shownShifts = Shifts::ALL_SHIFTS;
        namelistWidget->changeShownShifts();
    });
    connect(morningShiftAction, &QAction::triggered, [this](){
        namelistWidget->shownShifts = Shifts::MORNING_SHIFT;
        namelistWidget->changeShownShifts();
    });
    connect(dayShiftAction, &QAction::triggered, [this](){
        namelistWidget->shownShifts = Shifts::DAY_SHIFT;
        namelistWidget->changeShownShifts();
    });
    connect(eveningShiftAction, &QAction::triggered, [this](){
        namelistWidget->shownShifts = Shifts::EVENING_SHIFT;
        namelistWidget->changeShownShifts();
    });

    shiftGroup = new QActionGroup(this);
    shiftGroup->addAction(allShiftsAction);
    shiftGroup->addAction(morningShiftAction);
    shiftGroup->addAction(dayShiftAction);
    shiftGroup->addAction(eveningShiftAction);
    shiftGroup->setExclusive(true);
    allShiftsAction->setChecked(true);

    printTableAct = new QAction(tr("&Printtaa taulukko"), this);
    connect(printTableAct, &QAction::triggered, namelistWidget, &NamelistWidget::printTable);

    connect(namelistWidget, &NamelistWidget::selectionChanged, this, &MainWindow::updateActions);
}

void MainWindow::createMenus()
{
    fileMenu = menuBar()->addMenu(tr("&Tiedosto"));
    fileMenu->addAction(openAct);
    fileMenu->addAction(saveAct);
    fileMenu->addSeparator();
    fileMenu->addAction(exitAct);

    toolMenu = menuBar()->addMenu(tr("&Työkalut"));
    toolMenu->addAction(addAct);
    toolMenu->addAction(editAct);
    toolMenu->addSeparator();
    toolMenu->addAction(removeAct);
    toolMenu->addSeparator();
    toolMenu->addAction(printTableAct);

    shiftMenu = menuBar()->addMenu(tr("&Vuoro"));
    shiftMenu->addAction(allShiftsAction);
    shiftMenu->addAction(morningShiftAction);
    shiftMenu->addAction(dayShiftAction);
    shiftMenu->addAction(eveningShiftAction);

    ticketMenu = menuBar()->addMenu(tr("&Aterialiput"));
    ticketMenu->addAction(printAct);
    ticketMenu->addAction(setDepartmentAction);
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
    connect(addPersonButton, SIGNAL(clicked()), namelistWidget, SLOT(showAddEntryDialog()));

    editPersonButton = new QPushButton(tr("Muokkaa"), this);
    editPersonButton->setEnabled(false);
    buttonLayout->addWidget(editPersonButton);
    connect(editPersonButton, SIGNAL(clicked()), namelistWidget, SLOT(editEntry()));

    removePersonButton = new QPushButton(tr("Poista"), this);
    removePersonButton->setEnabled(false);
    buttonLayout->addWidget(removePersonButton);
    connect(removePersonButton, SIGNAL(clicked()), namelistWidget, SLOT(removeEntry()));

    drawTicketsButton = new QPushButton(tr("Piirrä aterialiput"), this);
    buttonLayout->addWidget(drawTicketsButton);
    connect(drawTicketsButton, &QPushButton::clicked, ticketWidget, &TicketWidget::printTickets);
}

void MainWindow::createTabs()
{
    namelistWidget = new NamelistWidget(this);
    ticketWidget = new TicketWidget(this);
    mainWidget->addTab(namelistWidget, tr("Nimilista"));
    setCentralWidget(mainWidget);
    mainWidget->setCurrentIndex(0);
    //mainWidget->addTab(ticketWidget, tr("Lippu")); //Setting text and image positions to the ticket from program doesn't work correctly at the moment
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
        return;
    }
    QDataStream out(&settingsFile);
    out << department;
}

void MainWindow::loadSettings()
{
    QFile settingsFile("settings");
    if(!settingsFile.open(QIODevice::ReadOnly)) {
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

QList<Person> MainWindow::getPeople()
{
    return namelistWidget->table->getPeople();
}
