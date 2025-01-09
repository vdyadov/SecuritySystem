#include "clientdata.h"
#include "ui_clientdata.h"

#include "generalemployee.h"

#include <QCheckBox>

ClientData::ClientData(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ClientData)
{
    ui->setupUi(this);
    loadEmployees();
}

ClientData::~ClientData()
{
    delete ui;
}

void ClientData::loadEmployees()
{
    GeneralEmployee *gEmployee = new GeneralEmployee();

    gEmployee->loadFromFileOneEmployee();

    double summ = 0;

    ui->tableWidget->setRowCount(gEmployee->employeesPay.size());
    for (int i = 0; i < gEmployee->employeesPay.size(); ++i) {

        const Employee &employee = gEmployee->employeesPay[i];

        ui->tableWidget->setItem(i, 0, new QTableWidgetItem(employee.getLastName()));
        ui->tableWidget->setItem(i, 1, new QTableWidgetItem(employee.getFirstName()));
        ui->tableWidget->setItem(i, 2, new QTableWidgetItem(employee.getMiddleName()));
        ui->tableWidget->setItem(i, 3, new QTableWidgetItem(employee.getPost()));
        ui->tableWidget->setItem(i, 4, new QTableWidgetItem(QString::number(employee.getSalary())));
        summ += gEmployee->employeesPay[i].getSalary();
        summ += gEmployee->employeesPay[i].getPremium();
    }
    ui->lineEditPrice->setText(QString::number(summ));
}

void ClientData::on_pushButtonPay_clicked()
{


}

