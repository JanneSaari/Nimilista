//Dialog box for adding and editing persons information.

#ifndef ADDDIALOG_H
#define ADDDIALOG_H

#include <QDialog>
#include <QspinBox>
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
class QSpinBox;
class QCheckBox;
class QRadioButton;
class QComboBox;
class NamelistWidget;

class AddDialog : public QDialog
{
    Q_OBJECT

public:
    AddDialog(NamelistWidget *parent = 0);

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
