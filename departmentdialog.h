#ifndef DEPARTMENTDIALOG_H
#define DEPARTMENTDIALOG_H

#include "mainwindow.h"

#include <QDialog>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>

class DepartmentDialog : public QDialog
{
public:
    DepartmentDialog(MainWindow *parent = 0);

    QLineEdit* departmentName;

private:
    QMainWindow *parent;
    QLabel *label;
    QPushButton *okButton;
    QPushButton *cancelButton;
};

#endif // DEPARTMENTDIALOG_H
