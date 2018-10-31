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

#ifndef DEPARTMENTDIALOG_H
#define DEPARTMENTDIALOG_H

#include "mainwindow.h"

#include <QDialog>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>

//Simple dialog window for setting department.
//Shows currently set department or empty text field if it isn't set.
class DepartmentDialog : public QDialog
{
public:
    DepartmentDialog(MainWindow *parent = nullptr);

    QLineEdit* departmentName;

private:
    QMainWindow *parent;
    QLabel *label;
    QPushButton *okButton;
    QPushButton *cancelButton;
};

#endif // DEPARTMENTDIALOG_H
