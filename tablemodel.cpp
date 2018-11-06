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
    return MAX_COLUMNS;
}

QVariant TableModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (index.row() >= listOfPeople.size() || index.row() < 0)
        return QVariant();

    if (role == Qt::DisplayRole) {
        const auto &person = listOfPeople.at(index.row());

        if (index.column() == Columns::NAME)
            return person.name;
        else if (index.column() == Columns::WORKSTATIONS) {
            if(person.workstation == -1 || person.workstation == 0)
                return "Ei työpistettä";
            else
                return person.workstation;
        }
        else if (index.column() == Columns::SHIFT) {
            if(person.shift == 0)
                return tr("Aamu");
            else if(person.shift == 1)
                return tr("Päivä");
            else if(person.shift == 2)
                return tr("Ilta");
        }
        else if (index.column() == Columns::MONDAY){
            if(person.isMonday)
                return "X";
            }
        else if (index.column() == Columns::TUESDAY){
            if(person.isTuesday)
                return "X";
            }
        else if (index.column() == Columns::WEDNESDAY){
            if(person.isWednesday)
                return "X";
        }
        else if (index.column() == Columns::THURSDAY){
            if(person.isThursday)
                return "X";
            }
        else if (index.column() == Columns::FRIDAY){
            if(person.isFriday)
                return "X";
            }
        else if (index.column() == Columns::INFO)
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
            case Columns::NAME:
                return tr("Nimi");
            case Columns::WORKSTATIONS:
                return tr("Työpiste");
            case Columns::SHIFT:
                return tr("Vuoro");
            case Columns::MONDAY:
                return tr("Ma");
            case Columns::TUESDAY:
                return tr("Ti");
            case Columns::WEDNESDAY:
                return tr("Ke");
            case Columns::THURSDAY:
                return tr("To");
            case Columns::FRIDAY:
                return tr("Pe");
            case Columns::INFO:
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

        if (index.column() == Columns::NAME)
            person.name = value.toString();
        else if(index.column() == Columns::WORKSTATIONS)
            person.workstation = value.toInt();
        else if(index.column() == Columns::SHIFT)
            person.shift = value.toInt();
        else if(index.column() == Columns::MONDAY)
            person.isMonday = value.toBool();
        else if(index.column() == Columns::TUESDAY)
            person.isTuesday = value.toBool();
        else if(index.column() == Columns::WEDNESDAY)
            person.isWednesday = value.toBool();
        else if(index.column() == Columns::THURSDAY)
            person.isThursday = value.toBool();
        else if(index.column() == Columns::FRIDAY)
            person.isFriday = value.toBool();
        else if (index.column() == Columns::INFO)
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
