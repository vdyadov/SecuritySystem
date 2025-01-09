#include "legalentity.h"
#include "ui_legalentity.h"

#include "generalemployee.h"
#include "schedule.h"
#include "clientdata.h"

#include <QCheckBox>
#include <QLineEdit>
#include <QLabel>

LegalEntity::LegalEntity(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::LegalEntity)
{
    ui->setupUi(this);
    loadEmployees();
}

LegalEntity::~LegalEntity()
{
    delete ui;
}

void LegalEntity::loadEmployees()
{
    GeneralEmployee *gEmployee = new GeneralEmployee();

    const QList<Employee> &employees = gEmployee->getEmployeesIsSched();
    ui->tableWidget->setRowCount(employees.size());
    for (int i = 0; i < employees.size(); ++i) {
        QCheckBox *checkBoxIsGun = new QCheckBox();
        QPushButton *psuhButtonTake = new QPushButton("Нанять");
        // QPushButton *psuhButtonRemoveEmployee = new QPushButton("Уволить");

        const Employee &employee = employees[i];

        checkBoxIsGun->setChecked(employee.getIsGun());
        checkBoxIsGun->setEnabled(false);

        connect(psuhButtonTake, &QPushButton::clicked, this, [this, i]() {
            onChangeEmployeeClicked(i);
        });

        // connect(psuhButtonRemoveEmployee, &QPushButton::clicked, this, [=]() {
        //     gEmployee->removeEmployee(i);  // Удаление сотрудника
        //     loadEmployees();  // Перезагрузка таблицы
        // });

        ui->tableWidget->setItem(i, 0, new QTableWidgetItem(employee.getLastName()));
        ui->tableWidget->setItem(i, 1, new QTableWidgetItem(employee.getFirstName()));
        ui->tableWidget->setItem(i, 2, new QTableWidgetItem(employee.getMiddleName()));
        ui->tableWidget->setItem(i, 3, new QTableWidgetItem(employee.getPost()));
        ui->tableWidget->setItem(i, 4, new QTableWidgetItem(QString::number(employee.getSalary())));
        ui->tableWidget->setItem(i, 5, new QTableWidgetItem(employee.getSpecialEquipment()));
        ui->tableWidget->setCellWidget(i, 6, checkBoxIsGun);
        ui->tableWidget->setCellWidget(i, 7, psuhButtonTake);
    }
}

void LegalEntity::onChangeEmployeeClicked(int i)
{
    GeneralEmployee *genEmployee = new GeneralEmployee();

    QList<Employee> employees = genEmployee->getEmployees();

    genEmployee->employeesPay.append(employees[i]);

    genEmployee->saveToFileOneEmployee();

}

void LegalEntity::on_pushButtonSchedule_clicked()
{
    // Создание окна с графиком
    GeneralEmployee *gEmployee = new GeneralEmployee();
    QList<Employee> employees = gEmployee->getEmployeesIsSched();
    // Создание и отображение виджета
    Schedule *scheduleWidget = new Schedule();
    scheduleWidget->generateSchedule(employees, QDate::currentDate(), 30);
    scheduleWidget->show();
    // QPushButton *saveSchedule = new QPushButton("Сохранить график");
    // connect(saveSchedule, &QPushButton::clicked, scheduleWidget, &Schedule::saveToJson);
    // scheduleWidget->layout()->addWidget(saveSchedule);
}


void LegalEntity::on_pushButtonPayment_clicked()
{
    ClientData *legalClient = new ClientData();

    QLineEdit *lineEditName = new QLineEdit();
    QLabel *labelName = new QLabel("Название фирмы");
    legalClient->layout()->addWidget(lineEditName);
    legalClient->layout()->addWidget(labelName);

    legalClient->show();
}

