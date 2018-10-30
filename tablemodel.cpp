#include "tablemodel.h"

TableModel::TableModel(QObject *parent)
    : QAbstractTableModel(parent)
{
}

int TableModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return listOfPeople.size();
}

int TableModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return 9;
}

QVariant TableModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (index.row() >= listOfPeople.size() || index.row() < 0)
        return QVariant();

    if (role == Qt::DisplayRole) {
        const auto &person = listOfPeople.at(index.row());

        if (index.column() == 0)
            return person.name;
        else if (index.column() == 1) {
            if(person.workstation == -1 || person.workstation == 0)
                return "Ei työpistettä";
            else
                return person.workstation;
        }
        else if (index.column() == 2) {
            if(person.shift == 0)
                return tr("Aamu");
            else if(person.shift == 1)
                return tr("Päivä");
            else if(person.shift == 2)
                return tr("Ilta");
        }
        else if (index.column() == 3){
            if(person.isMonday)
                return "X";
            }
        else if (index.column() == 4){
            if(person.isTuesday)
                return "X";
            }
        else if (index.column() == 5){
            if(person.isWednesday)
                return "X";
        }
        else if (index.column() == 6){
            if(person.isThursday)
                return "X";
            }
        else if (index.column() == 7){
            if(person.isFriday)
                return "X";
            }
        else if (index.column() == 8)
            return person.information;
    }
    return QVariant();
}

QVariant TableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole)
        return QVariant();

    if (orientation == Qt::Horizontal) {
        switch (section) {
            case 0:
                return tr("Nimi");
            case 1:
                return tr("Työpiste");
            case 2:
                return tr("Vuoro");
            case 3:
                return tr("Ma");
            case 4:
                return tr("Ti");
            case 5:
                return tr("Ke");
            case 6:
                return tr("To");
            case 7:
                return tr("Pe");
            case 8:
                return tr("Lisätietoa");

            default:
                return QVariant();
        }
    }
    return QVariant();
}

bool TableModel::insertRows(int position, int rows, const QModelIndex &index)
{
    Q_UNUSED(index);
    beginInsertRows(QModelIndex(), position, position + rows - 1);

    for (int row = 0; row < rows; ++row) {
        listOfPeople.insert(position, Person());
    }

    endInsertRows();
    return true;
}

bool TableModel::removeRows(int position, int rows, const QModelIndex &index)
{
    Q_UNUSED(index);
    beginRemoveRows(QModelIndex(), position, position + rows - 1);

    for (int row = 0; row < rows; ++row){
        listOfPeople.removeAt(position);
    }
    endRemoveRows();
    return true;
}

bool TableModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (index.isValid() && role == Qt::EditRole) {
        int row = index.row();

        auto person = listOfPeople.value(row);

        if (index.column() == 0)
            person.name = value.toString();
        else if(index.column() == 1)
            person.workstation = value.toInt();
        else if(index.column() == 2)
            person.shift = value.toInt();
        else if(index.column() == 3)
            person.isMonday = value.toBool();
        else if(index.column() == 4)
            person.isTuesday = value.toBool();
        else if(index.column() == 5)
            person.isWednesday = value.toBool();
        else if(index.column() == 6)
            person.isThursday = value.toBool();
        else if(index.column() == 7)
            person.isFriday = value.toBool();
        else if (index.column() == 8)
            person.information = value.toString();
        else
            return false;

        listOfPeople.replace(row, person);
        emit(dataChanged(index, index));

        return true;
    }

    return false;
}

Qt::ItemFlags TableModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::ItemIsEnabled;

    return QAbstractTableModel::flags(index) | Qt::ItemIsEditable;
}

QList<Person> TableModel::getPeople() const
{
    return listOfPeople;
}

void TableModel::resetTable()
{
    if(!listOfPeople.isEmpty())
        removeRows(0, listOfPeople.size(), QModelIndex());
}
