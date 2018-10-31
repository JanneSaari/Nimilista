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

#ifndef ADDDIALOG_H
#define ADDDIALOG_H

#include <QDialog>
#include <QCheckBox>
#include <QRadioButton>
#include <QComboBox>
#include <QVector>
#include <QGroupBox>

#include "workstations.h"

class QLabel;
class QPushButton;
class QTextEdit;
class QLineEdit;
class QCheckBox;
class QRadioButton;
class QComboBox;
class NamelistWidget;

//Dialog box for adding and editing persons information.

class AddDialog : public QDialog
{
    Q_OBJECT

public:
    AddDialog(NamelistWidget *parent = nullptr);

    QLineEdit *nameText;
    QTextEdit *informationText;
    QButtonGroup *shift;
    QRadioButton *morning;
    QRadioButton *day;
    QRadioButton *evening;
    QCheckBox *monday;
    QCheckBox *tuesday;
    QCheckBox *wednesday;
    QCheckBox *thursday;
    QCheckBox *friday;
    QGroupBox *workstationGroupBox;
    QButtonGroup *workstationButtonGroup;
    QRadioButton *workstationRadioButton;

    //Track workstation and shift of the edited person so that we can enable that button after updating workstation list.
    int editedPersonWorkstation = 0;
    int editedPersonShift = -1;

private:
    NamelistWidget *parent;
    QLabel *nameLabel;
    QLabel *informationLabel;
    QLabel *workstationLabel;
    QLabel *daysLabel;
    QPushButton *okButton;
    QPushButton *cancelButton;

    QVector<ReservedWorkstation> ReservedMorningWorkstations;
    QVector<ReservedWorkstation> ReservedDayWorkstations;
    QVector<ReservedWorkstation> ReservedEveningWorkstations;
    int numberOfWorkstations;

public slots:
    void updateWorkstationList();
};

#endif // ADDDIALOG_H
