#include "adddialog.h"
#include "tablemodel.h"
#include "namelistwidget.h"

#include <QtWidgets>

AddDialog::AddDialog(NamelistWidget *parent)
    : parent(parent)

{
    numberOfWorkstations = parent->workstations->getNumberOfWorkstations();
    occupiedEveningWorkstations = parent->workstations->getOccupiedEveningWorkstations();
    occupiedMorningWorkstations = parent->workstations->getOccupiedMorningWorkstations();

    nameLabel = new QLabel("Nimi");
    informationLabel = new QLabel("Lisätietoa");

    nameText = new QLineEdit;
    informationText = new QTextEdit;

    workstationGroupBox = new QGroupBox("Työpisteet");
    workstationButtonGroup = new QButtonGroup();
    QGridLayout *radioButtonLayout = new QGridLayout();

    int rows = 0;
    int column = 0;
    for(int iii = 1; iii <= numberOfWorkstations; ++iii)
    {
        //Use QButtonGroup.button(int id) to get single button or
        //QButtongroup.buttons() to get list of buttons in namelistWidget
        workstationRadioButton = new QRadioButton(QString::number(iii));
        radioButtonLayout->addWidget(workstationRadioButton, rows, column, Qt::AlignLeft);
        workstationButtonGroup->addButton(workstationRadioButton);
        workstationButtonGroup->setId(workstationRadioButton, iii);
        column++;
        if(iii % 10 == 0) {
            rows++;
            column = 0;
        }
    }
    workstationRadioButton = new QRadioButton("Ei työpistettä");
    radioButtonLayout->addWidget(workstationRadioButton, rows, column, Qt::AlignLeft);
    workstationButtonGroup->addButton(workstationRadioButton);
    workstationButtonGroup->setId(workstationRadioButton, 0);

    workstationGroupBox->setLayout(radioButtonLayout);

    morning = new QRadioButton("Aamu", this);
    evening = new QRadioButton("Ilta", this);

    monday = new QCheckBox("Ma", this);
    tuesday = new QCheckBox("Ti", this);
    wednesday = new QCheckBox("Ke", this);
    thursday = new QCheckBox("To", this);
    friday = new QCheckBox("Pe", this);

    okButton = new QPushButton("OK");
    cancelButton = new QPushButton("Peruuta");

    QGridLayout *gLayout = new QGridLayout;
    gLayout->setColumnStretch(2, 2);
    gLayout->addWidget(nameLabel, 0, 0);
    gLayout->addWidget(nameText, 0, 1);

    QVBoxLayout *morningOrEveningLayout = new QVBoxLayout;
    morningOrEveningLayout->addWidget(morning);
    morningOrEveningLayout->addWidget(evening);

    QHBoxLayout *daysLayout = new QHBoxLayout;
    daysLayout->addWidget(monday);
    daysLayout->addWidget(tuesday);
    daysLayout->addWidget(wednesday);
    daysLayout->addWidget(thursday);
    daysLayout->addWidget(friday);

    gLayout->addLayout(morningOrEveningLayout, 1, 0, Qt::AlignLeft);
    gLayout->addLayout(daysLayout, 1, 1, Qt::AlignLeft);

    gLayout->addWidget(workstationGroupBox, 1, 2, Qt::AlignRight);

    gLayout->addWidget(informationLabel, 2, 0, Qt::AlignLeft|Qt::AlignTop);
    gLayout->addWidget(informationText, 2, 1, Qt::AlignLeft);

    QHBoxLayout *buttonLayout = new QHBoxLayout;
    buttonLayout->addWidget(okButton);
    buttonLayout->addWidget(cancelButton);

    gLayout->addLayout(buttonLayout, 3, 1, Qt::AlignRight);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addLayout(gLayout);
    setLayout(mainLayout);

    connect(okButton, &QAbstractButton::clicked, this, &QDialog::accept);
    connect(cancelButton, &QAbstractButton::clicked, this, &QDialog::reject);

    connect(morning, &QRadioButton::toggled, this, &AddDialog::updateWorkstationList);
    morning->setChecked(true);

    setWindowTitle(tr("Lisää Henkilö"));
}

void AddDialog::updateWorkstationList()
{
    //TODO get name and display it
    if(evening->isChecked())
        for(int iii = 1; iii <= numberOfWorkstations; iii++) {
            OccupiedWorkstation testi(iii, " ");
            if(occupiedEveningWorkstations.contains(testi)) {
                workstationButtonGroup->button(0)->setChecked(true);
                workstationButtonGroup->button(iii)->setEnabled(false);
//                workstationButtonGroup->button(iii)->setText("qweqe");
            }
            else {
                workstationButtonGroup->button(iii)->setEnabled(true);
                workstationButtonGroup->button(iii)->setText(QString::number(iii));
            }
        }
    if(morning->isChecked())
        for(int iii = 1; iii <= numberOfWorkstations; iii++) {
            OccupiedWorkstation testi(iii, " ");
            if(occupiedMorningWorkstations.contains(testi)) {
                workstationButtonGroup->button(0)->setChecked(true);
                workstationButtonGroup->button(iii)->setEnabled(false);
            }
            else {
                workstationButtonGroup->button(iii)->setEnabled(true);
                workstationButtonGroup->button(iii)->setText(QString::number(iii));
            }
        }
}
