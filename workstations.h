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
