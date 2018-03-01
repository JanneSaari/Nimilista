#ifndef PERSON_H
#define PERSON_H

#include <QString>
#include <QDataStream>

class Person
{
public:
    QString name;
    int workstation;
    bool isEvening;
    bool isMonday;
    bool isTuesday;
    bool isWednesday;
    bool isThursday;
    bool isFriday;
    QString information;

    Person();
//    Person(QString name = "Esimerkki",  int workstation = 1, bool isEvening = false,
//           bool isMonday = false, bool isTuesday = false, bool isWednesday = false,
//           bool isThursday = false, bool isFriday = false, QString information = "Esimerkki tekstiä");

    bool operator==(const Person &other) const
    {
        return name == other.name;
//                && workstation == other.workstation && isEvening == other.isEvening
//                && isMonday == other.isMonday && isTuesday == other.isTuesday && isWednesday == other.isWednesday
//                && isThursday == other.isThursday && isFriday == other.isFriday &&information == other.information;
    }
};

inline QDataStream &operator<<(QDataStream &stream, const Person &person)
{
    return stream << person.name << person.workstation << person.isEvening
                  << person.isMonday << person.isTuesday << person.isWednesday
                  << person.isThursday << person.isFriday << person.information;
}

inline QDataStream &operator>>(QDataStream &stream, Person &person)
{
    return stream >> person.name >> person.workstation >> person.isEvening
                  >> person.isMonday >> person.isTuesday >> person.isWednesday
                  >> person.isThursday >> person.isFriday >> person.information;
}

#endif // PERSON_H
