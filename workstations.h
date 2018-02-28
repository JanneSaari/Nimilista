#ifndef WORKSTATIONS_H
#define WORKSTATIONS_H

//Keeps track of status of the workstations.
//If station is taken, save name of the occupier.
//AddDialog uses this to disable selectors for already occupied workstations

#include <QVector>

#include "tablemodel.h"
#include "person.h"

struct OccupiedWorkstation
{
    int workstation;
    QString name;

    OccupiedWorkstation(int workstation, QString name);

    bool operator==(const int &other) const
    {
        return workstation == other;
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
    int numberOfWorkstations;
};

#endif // WORKSTATIONS_H
