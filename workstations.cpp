#include "workstations.h"

Workstations::Workstations()
{
}

ReservedWorkstation::ReservedWorkstation()
{
}

ReservedWorkstation::ReservedWorkstation(const ReservedWorkstation &ReservedWorkstation)
    :workstation(ReservedWorkstation.workstation), name(ReservedWorkstation.name)
{
}

ReservedWorkstation::ReservedWorkstation(int workstation, QString name)
    :workstation(workstation), name(name)
{
}

void Workstations::freeWorkstation(const Person &person)
{
    ReservedWorkstation ReservedWorkstation(person.workstation, person.name);
    if(person.shift == 0) {
        if(morningWorkstations.contains(ReservedWorkstation)) {
            int index = morningWorkstations.indexOf(ReservedWorkstation);
            morningWorkstations.removeAt(index);
        }
    }
    else if(person.shift == 1) {
        if(dayWorkstations.contains(ReservedWorkstation)) {
            int index = dayWorkstations.indexOf(ReservedWorkstation);
            dayWorkstations.removeAt(index);
        }
    }
    else if(person.shift == 2) {
        if(eveningWorkstations.contains(ReservedWorkstation)) {
            int index = eveningWorkstations.indexOf(ReservedWorkstation);
            eveningWorkstations.removeAt(index);
        }
    }
}

void Workstations::setWorkstation(const Person &person)
{
    ReservedWorkstation ReservedWorkstation(person.workstation, person.name);
    if(person.shift == 0) {
        if(!morningWorkstations.contains(ReservedWorkstation))
            morningWorkstations.append(ReservedWorkstation);
    }
    else if(person.shift == 1) {
        if(!dayWorkstations.contains(ReservedWorkstation))
            dayWorkstations.append(ReservedWorkstation);
    }
    else if(person.shift == 2) {
        if(!eveningWorkstations.contains(ReservedWorkstation))
            eveningWorkstations.append(ReservedWorkstation);
    }
}

QVector<ReservedWorkstation> Workstations::getReservedMorningWorkstations() const
{
    return morningWorkstations;
}

QVector<ReservedWorkstation> Workstations::getReservedDayWorkstations() const
{
    return dayWorkstations;
}

QVector<ReservedWorkstation> Workstations::getReservedEveningWorkstations() const
{
    return eveningWorkstations;
}

int Workstations::getNumberOfWorkstations() const
{
    return numberOfWorkstations;
}
