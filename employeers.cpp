#include "employeers.h"
#include "ui_employeers.h"
#include "generalemployee.h"

#include "ui_addnewemployee.h"
#include "addnewemployee.h"

#include "ui_changeemployee.h"
#include "changeemployee.h"

#include "schedule.h"

Employeers::Employeers(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Employeers)
{
    ui->setupUi(this);
    loadEmployees();
    ui->tableWidget->setColumnWidth(0, 140);
    ui->tableWidget->setColumnWidth(5, 57);
    ui->tableWidget->setColumnWidth(6, 52);
}

Employeers::~Employeers()
{
    delete ui;
}

void Employeers::on_pushButtonAddEmployee_clicked()
{
    AddNewEmployee *addEmployee = new AddNewEmployee();
    // GeneralEmployee *gEmployee = new GeneralEmployee();
    connect(addEmployee, &AddNewEmployee::updateTableRequested, this, &Employeers::loadEmployees);
    // loadEmployees();
    addEmployee->show();
}

void Employeers::loadEmployees()
{
    GeneralEmployee *gEmployee = new GeneralEmployee();

    const QList<Employee> &employees = gEmployee->getEmployees();
    ui->tableWidget->setRowCount(employees.size());
    for (int i = 0; i < employees.size(); ++i) {
        QCheckBox *checkBoxIsGun = new QCheckBox();
        QPushButton *psuhButtonChangeEmployee = new QPushButton("Изменить");
        QPushButton *psuhButtonRemoveEmployee = new QPushButton("Уволить");

        const Employee &employee = employees[i];

        checkBoxIsGun->setChecked(employee.getIsGun());
        checkBoxIsGun->setEnabled(false);

        connect(psuhButtonChangeEmployee, &QPushButton::clicked, this, [this, i]() {
            onChangeEmployeeClicked(i);
        });

        connect(psuhButtonRemoveEmployee, &QPushButton::clicked, this, [=]() {
            gEmployee->removeEmployee(i);  // Удаление сотрудника
            loadEmployees();  // Перезагрузка таблицы
        });

        ui->tableWidget->setItem(i, 0, new QTableWidgetItem(employee.getIdNumber()));
        ui->tableWidget->setItem(i, 1, new QTableWidgetItem(employee.getFirstName()));
        ui->tableWidget->setItem(i, 2, new QTableWidgetItem(employee.getLastName()));
        ui->tableWidget->setItem(i, 3, new QTableWidgetItem(employee.getMiddleName()));
        ui->tableWidget->setItem(i, 4, new QTableWidgetItem(employee.getPost()));
        ui->tableWidget->setItem(i, 5, new QTableWidgetItem(QString::number(employee.getSalary())));
        ui->tableWidget->setCellWidget(i, 6, checkBoxIsGun);
        ui->tableWidget->setItem(i, 7, new QTableWidgetItem(employee.getSpecialEquipment()));
        ui->tableWidget->setCellWidget(i, 8, psuhButtonChangeEmployee);
        ui->tableWidget->setCellWidget(i, 9, psuhButtonRemoveEmployee);
    }
}

void Employeers::onChangeEmployeeClicked(int i)
{
    ChangeEmployee *cEmployee = new ChangeEmployee();
    // Получаем ссылку на объект GeneralEmployee
    GeneralEmployee *gEmployee = new GeneralEmployee();

    // Получаем данные текущего сотрудника
    const Employee &currentEmployee = gEmployee->getEmployees().at(i);

    cEmployee->setEmployeeData(currentEmployee);

    // Обработка сигнала обновления данных
    connect(cEmployee, &ChangeEmployee::updateTableRequested, this, [this, i, gEmployee, cEmployee]() {
        // Получаем обновлённые данные сотрудника из формы
        Employee updatedEmployee = cEmployee->getUpdatedEmployee();

        // Обновляем данные сотрудника в коллекции
        gEmployee->updateEmployee(i, updatedEmployee);

        // Перезагружаем таблицу
        loadEmployees();

        // Удаляем форму изменения после завершения
        cEmployee->deleteLater();
    });

    cEmployee->show();

}

void Employeers::on_pushButtonSchedule_clicked()
{
    // Создание окна с графиком
    GeneralEmployee *gEmployee = new GeneralEmployee();
    QList<Employee> employees = gEmployee->getEmployeesIsSched();
    // employees.append(Employee("Иван", "Иванов", "Иванович", "Адрес 1", "Должность 1", 50000, 10000, true, "АК-47", "12345", "Спец.оборудование 1", "ID123", "LIC123", "TAX123", "PENS123"));
    // employees.append(Employee("Петр", "Петров", "Петрович", "Адрес 2", "Должность 2", 55000, 12000, false, "", "", "Спец.оборудование 2", "ID124", "LIC124", "TAX124", "PENS124"));

    // Создание и отображение виджета
    Schedule *scheduleWidget = new Schedule();
    scheduleWidget->generateSchedule(employees, QDate::currentDate(), 30);
    scheduleWidget->show();
    QPushButton *saveSchedule = new QPushButton("Сохранить график");
    connect(saveSchedule, &QPushButton::clicked, scheduleWidget, &Schedule::saveToJson);
    scheduleWidget->layout()->addWidget(saveSchedule);
}

