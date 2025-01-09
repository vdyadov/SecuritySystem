#ifndef ADDNEWEMPLOYEE_H
#define ADDNEWEMPLOYEE_H

#include <QWidget>

#include "generalemployee.h"

namespace Ui {
class AddNewEmployee;
}

class AddNewEmployee : public QWidget, public GeneralEmployee
{
    Q_OBJECT

public:
    explicit AddNewEmployee(QWidget *parent = nullptr);
    ~AddNewEmployee();

private slots:
    void on_pushButtonAddEmployee_clicked();

private:
    Ui::AddNewEmployee *ui;

signals:
    void updateTableRequested();
};

#endif // ADDNEWEMPLOYEE_H
