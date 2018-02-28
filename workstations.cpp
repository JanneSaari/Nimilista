#include "workstations.h"

Workstations::Workstations()
{

}

OccupiedWorkstation::OccupiedWorkstation(int workstation, QString name)
    :workstation(workstation), name(name)
{
}

void Workstations::freeWorkstation(const Person person)
{
    OccupiedWorkstation occupiedWorkstation(person.workstation, person.name);
    if(person.isEvening) {
        if(eveningWorkstations.contains(occupiedWorkstation)) {
            int index = eveningWorkstations.indexOf(occupiedWorkstation.workstation);
            eveningWorkstations.removeAt(index);
        }
    }
    else if(!person.isEvening) {
        if(morningWorkstations.contains(occupiedWorkstation)) {
            int index = morningWorkstations.indexOf(occupiedWorkstation.workstation);
            morningWorkstations.removeAt(index);
        }
    }
}

void Workstations::setWorkstation(const Person person)
{
    OccupiedWorkstation occupiedWorkstation(person.workstation, person.name);
    if(person.isEvening) {
        if(!eveningWorkstations.contains(occupiedWorkstation))
            eveningWorkstations.append(occupiedWorkstation);
    }
    else if(!person.isEvening) {
        if(!morningWorkstations.contains(occupiedWorkstation))
            morningWorkstations.append(occupiedWorkstation);
    }
}

QVector<OccupiedWorkstation> Workstations::getOccupiedMorningWorkstations() const
{
    return morningWorkstations;
}

QVector<OccupiedWorkstation> Workstations::getOccupiedEveningWorkstations() const
{
    return eveningWorkstations;
}

int Workstations::getNumberOfWorkstations() const
{
    return numberOfWorkstations;
}
