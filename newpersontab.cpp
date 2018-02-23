#include "adddialog.h"
#include "newpersontab.h"

#include <QtWidgets>

NewPersonTab::NewPersonTab(QWidget *parent)
{
    Q_UNUSED(parent);

    descriptionLabel = new QLabel(tr("There are currently no contacts in your address book. "
                                      "\nClick Add to add new contacts."));

    addButton = new QPushButton(tr("Add"));

    connect(addButton, &QAbstractButton::clicked, this, &NewPersonTab::addEntry);

    mainLayout = new QVBoxLayout;
    mainLayout->addWidget(descriptionLabel, 0, Qt::AlignCenter);
    mainLayout->addWidget(addButton, 0, Qt::AlignCenter);

    setLayout(mainLayout);
}

void NewPersonTab::addEntry()
{
//    AddDialog aDialog();

//    if (aDialog.exec()) {
//        Person person;
//        person.name = aDialog.nameText->text();
//        person.isEvening = aDialog.evening->isChecked();

//        person.isMonday = aDialog.monday->isChecked();
//        person.isTuesday = aDialog.tuesday->isChecked();
//        person.isWednesday = aDialog.wednesday->isChecked();
//        person.isThursday = aDialog.thursday->isChecked();
//        person.isFriday = aDialog.friday->isChecked();

//        person.workstation = aDialog.workstationSelection->value();
//        person.information = aDialog.informationText->toPlainText();

//        emit sendDetails(person);
//    }
}
