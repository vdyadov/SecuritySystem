#ifndef CHANGEEMPLOYEE_H
#define CHANGEEMPLOYEE_H

#include <QWidget>

#include "employee.h"
#include "generalemployee.h"

namespace Ui {
class ChangeEmployee;
}

class ChangeEmployee : public QWidget
{
    Q_OBJECT

public:
    explicit ChangeEmployee(QWidget *parent = nullptr);
    ~ChangeEmployee();
    void setEmployeeData(const Employee &employee);
    Employee getUpdatedEmployee() const;
    // void onSaveButtonClicked();

private slots:
    void on_pushButtonAddEmployee_clicked();

private:
    Ui::ChangeEmployee *ui;

signals:
    void updateTableRequested();

};

#endif // CHANGEEMPLOYEE_H
