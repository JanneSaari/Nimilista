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
