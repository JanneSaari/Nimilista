#ifndef TABLEMODEL_H
#define TABLEMODEL_H

#include <QAbstractTableModel>
#include <QList>
#include <QBitArray>

#include "person.h"

//struct Person
//{
//    QString name;
//    int workstation;
//    bool isEvening;
//    bool isMonday;
//    bool isTuesday;
//    bool isWednesday;
//    bool isThursday;
//    bool isFriday;
//    QString information;

//    Person(QString name = "Esimerkki",  int workstation = 1, bool isEvening = false,
//           bool isMonday = false, bool isTuesday = false, bool isWednesday = false,
//           bool isThursday = false, bool isFriday = false, QString information = "Esimerkki tekstiä");

//    bool operator==(const Person &other) const
//    {
//        return name == other.name && workstation == other.workstation && isEvening == other.isEvening
//                && isMonday == other.isMonday && isTuesday == other.isTuesday && isWednesday == other.isWednesday
//                && isThursday == other.isThursday && isFriday == other.isFriday &&information == other.information;
//    }
//};

//inline QDataStream &operator<<(QDataStream &stream, const Person &person)
//{
//    return stream << person.name << person.workstation << person.isEvening
//                  << person.isMonday << person.isTuesday << person.isWednesday
//                  << person.isThursday << person.isFriday << person.information;
//}

//inline QDataStream &operator>>(QDataStream &stream, Person &person)
//{
//    return stream >> person.name >> person.workstation >> person.isEvening
//                  >> person.isMonday >> person.isTuesday >> person.isWednesday
//                  >> person.isThursday >> person.isFriday >> person.information;
//}

class TableModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    TableModel(QObject *parent = 0);

    int rowCount(const QModelIndex &parent) const override;
    int columnCount(const QModelIndex &parent) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
    Qt::ItemFlags flags(const QModelIndex &index) const override;
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;
    bool insertRows(int position, int rows, const QModelIndex &index = QModelIndex()) override;
    bool removeRows(int position, int rows, const QModelIndex &index = QModelIndex()) override;
    QList<Person> getPeople() const;
    void resetTable();
//    void setWorkstation(const Person person);
//    void freeWorkstation(const Person person);
//    int getNumberOfWorkstations();
//    QVector<int> getFreeMorningWorkstations() const;
//    QVector<int> getFreeEveningWorkstations() const;

private:
    QList<Person> listOfPeople;
//    QVector<int> freeMorningWorkstations;
//    QVector<int> freeEveningWorkstations;
//    int numberOfWorkstations = 50;
};

#endif // TABLEMODEL_H
