#include "adddialog.h"
#include "tablemodel.h"
#include "namelistwidget.h"

#include <QtWidgets>

AddDialog::AddDialog(NamelistWidget *parent)
    : parent(parent)

{
    numberOfWorkstations = parent->workstations->getNumberOfWorkstations();
    ReservedMorningWorkstations = parent->workstations->getReservedMorningWorkstations();
    ReservedDayWorkstations     = parent->workstations->getReservedDayWorkstations();
    ReservedEveningWorkstations = parent->workstations->getReservedEveningWorkstations();

    nameLabel = new QLabel(tr("Nimi"), this);
    nameText = new QLineEdit(this);
    informationLabel = new QLabel(tr("Lisätietoa"), this);
    informationText = new QTextEdit(this);

    workstationGroupBox = new QGroupBox(tr("Työpisteet"), this);
    workstationButtonGroup = new QButtonGroup(this);
    QGridLayout *radioButtonLayout = new QGridLayout(this);

    int rows = 0;
    int column = 0;
    for(int iii = 1; iii <= numberOfWorkstations; ++iii)
    {
        //Use QButtonGroup.button(int id) to get single button or
        //QButtongroup.buttons() to get list of buttons in namelistWidget
        workstationRadioButton = new QRadioButton(QString::number(iii), this);
        radioButtonLayout->addWidget(workstationRadioButton, rows, column, Qt::AlignLeft);
        workstationButtonGroup->addButton(workstationRadioButton);
        workstationButtonGroup->setId(workstationRadioButton, iii);
        column++;
        if(iii % 5 == 0) {
            rows++;
            column = 0;
        }
    }
    workstationRadioButton = new QRadioButton(tr("Ei työpistettä"), this);
    radioButtonLayout->addWidget(workstationRadioButton, rows, column, Qt::AlignLeft);
    workstationButtonGroup->addButton(workstationRadioButton);
    workstationButtonGroup->setId(workstationRadioButton, 0);

    workstationGroupBox->setLayout(radioButtonLayout);

    shift = new QButtonGroup(this);
    morning = new QRadioButton(tr("Aamu"), this);
    day = new QRadioButton(tr("Päivä"), this);
    evening = new QRadioButton(tr("Ilta"), this);
    shift->addButton(morning);
    shift->addButton(day);
    shift->addButton(evening);

    monday = new QCheckBox(tr("Ma"), this);
    tuesday = new QCheckBox(tr("Ti"), this);
    wednesday = new QCheckBox(tr("Ke"), this);
    thursday = new QCheckBox(tr("To"), this);
    friday = new QCheckBox(tr("Pe"), this);

    okButton = new QPushButton(tr("OK"), this);
    cancelButton = new QPushButton(tr("Peruuta"), this);

    QGridLayout *gLayout = new QGridLayout(this);
    gLayout->setColumnStretch(2, 2);
    gLayout->addWidget(nameLabel, 0, 0);
    gLayout->addWidget(nameText, 0, 1);

    QVBoxLayout *shiftLayout = new QVBoxLayout(this);
    shiftLayout->addWidget(morning);
    shiftLayout->addWidget(day);
    shiftLayout->addWidget(evening);

    QHBoxLayout *daysLayout = new QHBoxLayout(this);
    daysLayout->addWidget(monday);
    daysLayout->addWidget(tuesday);
    daysLayout->addWidget(wednesday);
    daysLayout->addWidget(thursday);
    daysLayout->addWidget(friday);

//    QVBoxLayout leftSideLayout;
//    leftSideLayout->addChildLayout(ShiftLayout);
//    leftSideLayout->addChildLayout(daysLayout);

    gLayout->addLayout(shiftLayout, 1, 0, Qt::AlignLeft);
    gLayout->addLayout(daysLayout, 1, 1, Qt::AlignLeft);

    gLayout->addWidget(workstationGroupBox, 1, 2, Qt::AlignRight);

    gLayout->addWidget(informationLabel, 2, 0, Qt::AlignLeft|Qt::AlignTop);
    gLayout->addWidget(informationText, 2, 1, Qt::AlignLeft);

    QHBoxLayout *buttonLayout = new QHBoxLayout(this);
    buttonLayout->addWidget(okButton);
    buttonLayout->addWidget(cancelButton);

    gLayout->addLayout(buttonLayout, 3, 1, Qt::AlignRight);

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->addLayout(gLayout);
    setLayout(mainLayout);

    connect(okButton, &QAbstractButton::clicked, this, &QDialog::accept);
    connect(cancelButton, &QAbstractButton::clicked, this, &QDialog::reject);

    connect(morning, QRadioButton::clicked, this, &AddDialog::updateWorkstationList);
    connect(day, QRadioButton::clicked, this, &AddDialog::updateWorkstationList);
    connect(evening, QRadioButton::clicked, this, &AddDialog::updateWorkstationList);
    morning->setChecked(true);
    updateWorkstationList();

    setWindowTitle(tr("Lisää Henkilö"));
}

void AddDialog::updateWorkstationList()
{
    if(morning->isChecked()){
        for(int iii = 1; iii <= numberOfWorkstations; iii++) {
            ReservedWorkstation testi(iii, " ");
            if(ReservedMorningWorkstations.contains(testi)) {
                workstationButtonGroup->button(0)->setChecked(true);
                workstationButtonGroup->button(iii)->setEnabled(false);
                workstationButtonGroup->button(iii)->setText(
                            QString::number(iii).append(" ")
                            += ReservedMorningWorkstations.at(ReservedMorningWorkstations.indexOf(testi)).name);
                if(editedPersonShift == 0) {
                    workstationButtonGroup->button(editedPersonWorkstation)->setEnabled(true);
                    workstationButtonGroup->button(editedPersonWorkstation)->setChecked(true);
                }
            }
            else {
                workstationButtonGroup->button(iii)->setEnabled(true);
                workstationButtonGroup->button(iii)->setText(QString::number(iii));
            }
        }
    }
    if(day->isChecked()) {
        for(int iii = 1; iii <= numberOfWorkstations; iii++) {
            ReservedWorkstation testi(iii, " ");
            if(ReservedDayWorkstations.contains(testi)) {
                workstationButtonGroup->button(0)->setChecked(true);
                workstationButtonGroup->button(iii)->setEnabled(false);
                workstationButtonGroup->button(iii)->setText(
                            QString::number(iii).append(" ")
                            += ReservedDayWorkstations.at(ReservedDayWorkstations.indexOf(testi)).name);
                if(editedPersonShift == 1) {
                    workstationButtonGroup->button(editedPersonWorkstation)->setEnabled(true);
                    workstationButtonGroup->button(editedPersonWorkstation)->setChecked(true);
                }
            }
            else {
                workstationButtonGroup->button(iii)->setEnabled(true);
                workstationButtonGroup->button(iii)->setText(QString::number(iii));
            }
        }
    }
    if(evening->isChecked()) {
        for(int iii = 1; iii <= numberOfWorkstations; iii++) {
            ReservedWorkstation testi(iii, " ");
            if(ReservedEveningWorkstations.contains(testi)) {
                workstationButtonGroup->button(0)->setChecked(true);
                workstationButtonGroup->button(iii)->setEnabled(false);
                workstationButtonGroup->button(iii)->setText(
                            QString::number(iii).append(" ")
                            += ReservedEveningWorkstations.at(ReservedEveningWorkstations.indexOf(testi)).name);
                if(editedPersonShift == 2) {
                    workstationButtonGroup->button(editedPersonWorkstation)->setEnabled(true);
                    workstationButtonGroup->button(editedPersonWorkstation)->setChecked(true);
                }
            }
            else {
                workstationButtonGroup->button(iii)->setEnabled(true);
                workstationButtonGroup->button(iii)->setText(QString::number(iii));
            }
        }
    }
}
