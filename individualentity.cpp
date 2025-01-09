#include "individualentity.h"
#include "ui_individualentity.h"

#include "generalemployee.h"
#include "clientdata.h"

#include <QCheckBox>
#include <QLineEdit>
#include <QLabel>

IndividualEntity::IndividualEntity(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::IndividualEntity)
{
    ui->setupUi(this);
    loadEmployees();
}

IndividualEntity::~IndividualEntity()
{
    delete ui;
}

void IndividualEntity::loadEmployees()
{
    GeneralEmployee *gEmployee = new GeneralEmployee();

    const QList<Employee> &employees = gEmployee->getEmployees();
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

void IndividualEntity::onChangeEmployeeClicked(int i)
{
    GeneralEmployee *genEmployee = new GeneralEmployee();

    QList<Employee> employees = genEmployee->getEmployees();

    genEmployee->employeesPay.append(employees[i]);

    genEmployee->saveToFileOneEmployee();
}

void IndividualEntity::on_pushButtonPayment_clicked()
{
    ClientData *individClient = new ClientData();

    QLineEdit *lineEditFirstName = new QLineEdit();
    QLabel *labelFirstName = new QLabel("Имя");
    QLineEdit *lineEditLastName = new QLineEdit();
    QLabel *labelLastName = new QLabel("Фамилия");
    QLineEdit *lineEditMiddleName = new QLineEdit();
    QLabel *labelMiddleName = new QLabel("Отчество");
    QLineEdit *lineEditPassport = new QLineEdit();
    QLabel *labelEditPassport = new QLabel("Паспортные данные");

    individClient->layout()->addWidget(lineEditFirstName);
    individClient->layout()->addWidget(labelFirstName);
    individClient->layout()->addWidget(lineEditLastName);
    individClient->layout()->addWidget(labelLastName);
    individClient->layout()->addWidget(lineEditMiddleName);
    individClient->layout()->addWidget(labelMiddleName);
    individClient->layout()->addWidget(lineEditPassport);
    individClient->layout()->addWidget(labelEditPassport);

    individClient->show();
}

