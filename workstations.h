#ifndef WORKSTATIONS_H
#define WORKSTATIONS_H

//Keeps track of status of the workstations.
//If station is taken, save name of the occupier.
//AddDialog uses this to disable selectors for already Reserved workstations.

#include <QVector>

#include "tablemodel.h"
#include "person.h"

//Tracks reserved workstation number and name of the reserver
struct ReservedWorkstation
{
    int workstation;
    QString name;

    ReservedWorkstation();
    ReservedWorkstation(const ReservedWorkstation &ReservedWorkstation);
    ReservedWorkstation(int workstation, QString name);

    inline bool operator==(const ReservedWorkstation& other) const
    {
        if(workstation == other.workstation)
            return true;
        else
            return false;
    }
};

class Workstations
{
public:
    Workstations();
    QVector<ReservedWorkstation> getReservedMorningWorkstations() const;
    QVector<ReservedWorkstation> getReservedDayWorkstations() const;
    QVector<ReservedWorkstation> getReservedEveningWorkstations() const;
    void setWorkstation(const Person &person);
    void freeWorkstation(const Person &person);
    int getNumberOfWorkstations() const;

private:
    //Used to keep track of the Reserved workstations
    QVector<ReservedWorkstation> morningWorkstations;
    QVector<ReservedWorkstation> dayWorkstations;
    QVector<ReservedWorkstation> eveningWorkstations;
    int numberOfWorkstations = 50;
};

#endif // WORKSTATIONS_H
