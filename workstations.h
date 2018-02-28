#ifndef WORKSTATIONS_H
#define WORKSTATIONS_H

//Keeps track of status of the workstations.
//If station is taken, save name of the occupier.
//AddDialog uses this to disable selectors for already occupied workstations.

#include <QVector>

#include "tablemodel.h"
#include "person.h"

struct OccupiedWorkstation
{
    int workstation;
    QString name;

    OccupiedWorkstation();
    OccupiedWorkstation(const OccupiedWorkstation &occupiedWorkstation);
    OccupiedWorkstation(int workstation, QString name);

    inline bool operator==(const OccupiedWorkstation& other) const
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
    QVector<OccupiedWorkstation> getOccupiedMorningWorkstations() const;
    QVector<OccupiedWorkstation> getOccupiedEveningWorkstations() const;
    void setWorkstation(const Person &person);
    void freeWorkstation(const Person &person);
    int getNumberOfWorkstations() const;

private:
    //Used to keep track of the occupied workstations
    QVector<OccupiedWorkstation> morningWorkstations;
    QVector<OccupiedWorkstation> eveningWorkstations;
    int numberOfWorkstations = 50;
};

#endif // WORKSTATIONS_H
