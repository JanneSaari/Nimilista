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
