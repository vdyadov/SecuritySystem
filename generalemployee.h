#ifndef GENERALEMPLOYEE_H
#define GENERALEMPLOYEE_H

#include <QWidget>
#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QTableWidget>

#include "employee.h"

class GeneralEmployee
{
public:
    void addEmployee(Employee &employee);
    void removeEmployee(int index);
    void updateEmployee(int index, const Employee &updatedEmployee);
    void saveToFile() const;
    void saveToFileOneEmployee() const;
    void saveToFileDelEmployee() const;
    const QList<Employee> &getEmployees() const;
    const QList<Employee> &getEmployeesIsSched() const;
    void loadFromFile();
    void loadFromFileOneEmployee();
    void loadFromFileDelEmployee();
    GeneralEmployee();
    QList<Employee> employeesDel;
    QList<Employee> employeesPay;

protected:
    QList<Employee> employees;

private:
    QString filePath = "/Users/vlad_os/study/kursach/SecuritySystem/SecuritySystem/build/employee.json";
    QString filePathDel = "/Users/vlad_os/study/kursach/SecuritySystem/SecuritySystem/build/del_employee.json";
    QString filePathPay = "/Users/vlad_os/study/kursach/SecuritySystem/SecuritySystem/build/pay_employee.json";
};

#endif // GENERALEMPLOYEE_H
