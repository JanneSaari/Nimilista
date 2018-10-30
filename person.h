#ifndef PERSON_H
#define PERSON_H

#include <QString>
#include <QDataStream>

enum Shift
{
    Morning,
    Day,
    Evening
};

class Person
{
public:
    QString name;
    int workstation;
    int shift;
    bool isMonday;
    bool isTuesday;
    bool isWednesday;
    bool isThursday;
    bool isFriday;
    QString information;

    Person();

    bool operator==(const Person &other) const
    {
        return name == other.name;
    }
};

inline QDataStream &operator<<(QDataStream &stream, const Person &person)
{
    return stream << person.name << person.workstation << person.shift
                  << person.isMonday << person.isTuesday << person.isWednesday
                  << person.isThursday << person.isFriday << person.information;
}

inline QDataStream &operator>>(QDataStream &stream, Person &person)
{
    return stream >> person.name >> person.workstation >> person.shift
                  >> person.isMonday >> person.isTuesday >> person.isWednesday
                  >> person.isThursday >> person.isFriday >> person.information;
}

#endif // PERSON_H
