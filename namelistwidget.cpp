#include "namelistwidget.h"
#include "adddialog.h"
#include "mealtickets.h"
#include "mainwindow.h"

#include <QtWidgets>

NamelistWidget::NamelistWidget(MainWindow *parent)
    : parent(parent)
{
    table = new TableModel(this);
    setupNamelist();
}

void NamelistWidget::showAddEntryDialog()
{
    AddDialog aDialog(this);
    if (aDialog.exec()) {
        Person person;
        person.name = aDialog.nameText->text();
        person.isEvening = aDialog.evening->isChecked();

        person.isMonday = aDialog.monday->isChecked();
        person.isTuesday = aDialog.tuesday->isChecked();
        person.isWednesday = aDialog.wednesday->isChecked();
        person.isThursday = aDialog.thursday->isChecked();
        person.isFriday = aDialog.friday->isChecked();

        person.workstation = aDialog.workstationButtonGroup->checkedId();
        person.information = aDialog.informationText->toPlainText();

        addEntry(person);
    }
}

void NamelistWidget::addEntry(Person person)
{

    //TODO check only if name matches
    if (!table->getPeople().contains({person.name})) {
        table->insertRows(0, 1, QModelIndex());

        QModelIndex index = table->index(0, 0, QModelIndex());
        table->setData(index, person.name, Qt::EditRole);
        index = table->index(0, 1, QModelIndex());
        table->setData(index, QVariant(person.workstation), Qt::EditRole);
        index = table->index(0, 2, QModelIndex());
        table->setData(index, QVariant(person.isEvening), Qt::EditRole);
        index = table->index(0, 3, QModelIndex());
        table->setData(index, QVariant(person.isMonday), Qt::EditRole);
        index = table->index(0, 4, QModelIndex());
        table->setData(index, QVariant(person.isTuesday), Qt::EditRole);
        index = table->index(0, 5, QModelIndex());
        table->setData(index, QVariant(person.isWednesday), Qt::EditRole);
        index = table->index(0, 6, QModelIndex());
        table->setData(index, QVariant(person.isThursday), Qt::EditRole);
        index = table->index(0, 7, QModelIndex());
        table->setData(index, QVariant(person.isFriday), Qt::EditRole);
        index = table->index(0, 8, QModelIndex());
        table->setData(index, person.information, Qt::EditRole);

        table->setWorkstation(person);

    } else if(!readingFromFile){
        QMessageBox::information(this, tr("Duplicate Name"),
            tr("The name \"%1\" already exists.").arg(person.name));
    }
}

void NamelistWidget::editEntry()
{
    {
        QTableView *temp = static_cast<QTableView*>(currentWidget());
        QSortFilterProxyModel *proxy = static_cast<QSortFilterProxyModel*>(temp->model());
        QItemSelectionModel *selectionModel = temp->selectionModel();
        QModelIndexList indexes = selectionModel->selectedRows();

        Person person;
        int row = -1;

        //Get selected persons values
        foreach (QModelIndex index, indexes) {
            row = proxy->mapToSource(index).row();

            QModelIndex nameIndex = table->index(row, 0, QModelIndex());
            QVariant varName = table->data(nameIndex, Qt::DisplayRole);
            person.name = varName.toString();

            QModelIndex workstationIndex = table->index(row, 1, QModelIndex());
            QVariant varWorkstation = table->data(workstationIndex, Qt::DisplayRole);
            person.workstation = varWorkstation.toUInt();

            QModelIndex eveningIndex = table->index(row, 2, QModelIndex());
            QVariant varEvening= table->data(eveningIndex, Qt::DisplayRole);
            if(varEvening == "Aamu")
                person.isEvening = false;
            else if(varEvening == "Ilta")
                person.isEvening = true;

            QModelIndex mondayIndex = table->index(row, 3, QModelIndex());
            QVariant varMonday= table->data(mondayIndex, Qt::DisplayRole);
            person.isMonday = varMonday.toBool();
            QModelIndex tuesdayIndex = table->index(row, 4, QModelIndex());
            QVariant varTuesday= table->data(tuesdayIndex, Qt::DisplayRole);
            person.isTuesday = varTuesday.toBool();
            QModelIndex wednesdayIndex = table->index(row, 5, QModelIndex());
            QVariant varWednesday= table->data(wednesdayIndex, Qt::DisplayRole);
            person.isWednesday = varWednesday.toBool();
            QModelIndex thursdayIndex = table->index(row, 6, QModelIndex());
            QVariant varThursday= table->data(thursdayIndex, Qt::DisplayRole);
            person.isThursday = varThursday.toBool();
            QModelIndex fridayIndex = table->index(row, 7, QModelIndex());
            QVariant varFriday= table->data(fridayIndex, Qt::DisplayRole);
            person.isFriday = varFriday.toBool();

            QModelIndex informationIndex = table->index(row, 8, QModelIndex());
            QVariant varInformation = table->data(informationIndex, Qt::DisplayRole);
            person.information = varInformation.toString();
        }

        //Open new addDialog window and set values to selected persons values
        AddDialog aDialog(this);
        aDialog.setWindowTitle(tr("Muokkaa henkilöä"));

        aDialog.nameText->setText(person.name);
        aDialog.informationText->setText(person.information);
        aDialog.workstationButtonGroup->button(person.workstation)->setChecked(true);
        aDialog.morning->setChecked(!person.isEvening);
        aDialog.evening->setChecked(person.isEvening);
        aDialog.monday->setChecked(person.isMonday);
        aDialog.tuesday->setChecked(person.isTuesday);
        aDialog.wednesday->setChecked(person.isWednesday);
        aDialog.thursday->setChecked(person.isThursday);
        aDialog.friday->setChecked(person.isFriday);

        //Get edited values and compare them to previous ones
        //and set new values if they changed
        Person newValues;
        if (aDialog.exec()) {
            newValues.workstation = aDialog.workstationButtonGroup->checkedId();
            if (newValues.workstation!= person.workstation) {
                QModelIndex index = table->index(row, 1, QModelIndex());
                table->setData(index, QVariant(newValues.workstation), Qt::EditRole);
            }
            newValues.isEvening= aDialog.evening->isChecked();
            if (newValues.isEvening!= person.isEvening) {
                QModelIndex index = table->index(row, 2, QModelIndex());
                table->setData(index, QVariant(newValues.isEvening), Qt::EditRole);
            }
            newValues.isMonday= aDialog.monday->isChecked();
            if (newValues.isMonday!= person.isMonday) {
                QModelIndex index = table->index(row, 3, QModelIndex());
                table->setData(index, QVariant(newValues.isMonday), Qt::EditRole);
            }
            newValues.isTuesday= aDialog.tuesday->isChecked();
            if (newValues.isTuesday!= person.isTuesday) {
                QModelIndex index = table->index(row, 4, QModelIndex());
                table->setData(index, QVariant(newValues.isTuesday), Qt::EditRole);
            }
            newValues.isWednesday= aDialog.wednesday->isChecked();
            if (newValues.isWednesday!= person.isWednesday) {
                QModelIndex index = table->index(row, 5, QModelIndex());
                table->setData(index, QVariant(newValues.isWednesday), Qt::EditRole);
            }
            newValues.isThursday= aDialog.thursday->isChecked();
            if (newValues.isThursday!= person.isThursday) {
                QModelIndex index = table->index(row, 6, QModelIndex());
                table->setData(index, QVariant(newValues.isThursday), Qt::EditRole);
            }
            newValues.isFriday= aDialog.friday->isChecked();
            if (newValues.isFriday!= person.isFriday) {
                QModelIndex index = table->index(row, 7, QModelIndex());
                table->setData(index, QVariant(newValues.isFriday), Qt::EditRole);
            }
            newValues.information = aDialog.informationText->toPlainText();
            if (newValues.information!= person.information) {
                QModelIndex index = table->index(row, 8, QModelIndex());
                table->setData(index, newValues.information, Qt::EditRole);
            }
        }
        table->freeWorkstation(person);
        table->setWorkstation(newValues);
    }
}

void NamelistWidget::removeEntry()
{
    QTableView *temp = static_cast<QTableView*>(currentWidget());
    QSortFilterProxyModel *proxy = static_cast<QSortFilterProxyModel*>(temp->model());
    QItemSelectionModel *selectionModel = temp->selectionModel();

    QModelIndexList indexes = selectionModel->selectedRows();

    foreach (QModelIndex index, indexes) {
        int row = proxy->mapToSource(index).row();
        table->removeRows(row, 1, QModelIndex());
    }
}

void NamelistWidget::setupNamelist()
{
    proxyModel = new QSortFilterProxyModel(this);
    proxyModel->setSourceModel(table);

    QTableView *tableView = new QTableView;
    tableView->setModel(proxyModel);

    tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    tableView->horizontalHeader()->setStretchLastSection(true);
    tableView->verticalHeader()->hide();
    tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    tableView->setSelectionMode(QAbstractItemView::SingleSelection);

    tableView->setSortingEnabled(true);

    connect(tableView->selectionModel(),
        &QItemSelectionModel::selectionChanged,
        this, &NamelistWidget::selectionChanged);

    connect(this, &QTabWidget::currentChanged, this, [this](int tabIndex) {
        auto *tableView = qobject_cast<QTableView *>(widget(tabIndex));
        if (tableView)
            emit selectionChanged(tableView->selectionModel()->selection());
    });

    addTab(tableView, "Henkilöt");
}

void NamelistWidget::readFromFile(const QString &fileName)
{
    QFile file(fileName);
    readingFromFile = true;

    if (!file.open(QIODevice::ReadOnly)) {
        QMessageBox::information(this, tr("Tiedostoa ei pystytty avaamaan."),
            file.errorString());
        return;
    }

    QList<Person> listOfPeople;
    QDataStream in(&file);
    in >> listOfPeople;

    if (listOfPeople.isEmpty()) {
        QMessageBox::information(this, tr("Ei henkilöitä tiedostossa."),
                                 tr("Tiedosto jonka yritit avata ei sisällä henkilöitä."));
    } else {
        table->resetTable();
        for (const auto &person: qAsConst(listOfPeople))
            addEntry(person);
    }
    readingFromFile = false;
}

void NamelistWidget::writeToFile(const QString &fileName)
{
    QFile file(fileName);

    if (!file.open(QIODevice::WriteOnly)) {
        QMessageBox::information(this, tr("Tiedostoa ei pystytty avaamaan."), file.errorString());
        return;
    }

    QDataStream out(&file);
    out << table->getPeople();
}

void NamelistWidget::printMealTickets()
{
    MealTickets tickets(this);
    tickets.printMealTickets();
}

//Getters
QVector<int> NamelistWidget::getFreeMorningWorkstations() const
{
    return table->getFreeMorningWorkstations();
}

QVector<int> NamelistWidget::getFreeEveningWorkstations() const
{
    return table->getFreeEveningWorkstations();
}

int NamelistWidget::getNumberOfWorkstations() const
{
    return table->getNumberOfWorkstations();
}

QString NamelistWidget::getDepartment() const
{
    return parent->getDepartment();
}

//Setters
void NamelistWidget::setDepartment(QString newDepartment)
{
    department = newDepartment;
}

