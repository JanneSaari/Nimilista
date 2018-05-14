#include "departmentdialog.h"

#include <QVBoxLayout>
#include <QHBoxLayout>

DepartmentDialog::DepartmentDialog(MainWindow *parent)
    :parent(parent)
{
    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    label = new QLabel(tr("Kirjoita pajan nimi joka kirjoitetaan aterialippuihin(esim. IT-paja)."), this);
    mainLayout->addWidget(label);

    departmentName = new QLineEdit(parent->getDepartment(), this);
    mainLayout->addWidget(departmentName);
    //Create ok and cancel buttons and add them to main layout
    QHBoxLayout* buttonLayout = new QHBoxLayout(this);
    okButton = new QPushButton(tr("Hyväksy"), this);
    cancelButton = new QPushButton(tr("Peruuta"), this);
    buttonLayout->addWidget(okButton);
    buttonLayout->addWidget(cancelButton);
    mainLayout->addLayout(buttonLayout);

    connect(okButton, &QAbstractButton::clicked, this, &QDialog::accept);
    connect(cancelButton, &QAbstractButton::clicked, this, &QDialog::reject);

    setLayout(mainLayout);
}
