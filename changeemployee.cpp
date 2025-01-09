#include "changeemployee.h"
#include "ui_changeemployee.h"

#include <QMessageBox>
// #include <QWidget>

#include "generalemployee.h"

ChangeEmployee::ChangeEmployee(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ChangeEmployee)
{
    ui->setupUi(this);
}

ChangeEmployee::~ChangeEmployee()
{
    delete ui;
}

void ChangeEmployee::on_pushButtonAddEmployee_clicked()
{
    emit updateTableRequested();
    close();
}

void ChangeEmployee::setEmployeeData(const Employee &employee) {
    ui->lineEditFirstName->setText(employee.getFirstName());
    ui->lineEditLastName->setText(employee.getLastName());
    ui->lineEditMiddleName->setText(employee.getMiddleName());
    ui->lineEditPost->setText(employee.getPost());
    ui->lineEditFirstName->setText(employee.getFirstName());
    ui->lineEditLastName->setText(employee.getLastName());
    ui->lineEditMiddleName->setText(employee.getMiddleName());
    ui->lineEditAddress->setText(employee.getAddress());
    ui->lineEditPost->setText(employee.getPost());
    ui->lineEditSalary->setText(QString::number(employee.getSalary()));
    ui->lineEditPremium->setText(QString::number(employee.getPremium()));
    ui->lineEditIDNumber->setText(employee.getIdNumber());
    ui->lineEditLicenseNumber->setText(employee.getLicenseNumber());
    ui->lineEditTaxNumber->setText(employee.getTaxNumber());
    ui->lineEditPensionNumber->setText(employee.getPensionNumber());
    ui->lineEditspecialEquipment->setText(employee.getSpecialEquipment());
    ui->checkBoxGun->setChecked(employee.getIsGun());
    ui->lineEditGunMark->setText(employee.getGunMark());
    ui->lineEditGunNumber->setText(employee.getGunMark());
    ui->checkBoxIsShedule->setChecked(employee.getIsSchedule());
}

Employee ChangeEmployee::getUpdatedEmployee() const {
    Employee updatedEmployee;

    updatedEmployee.setFirstName(ui->lineEditFirstName->text());
    updatedEmployee.setLastName(ui->lineEditLastName->text());
    updatedEmployee.setMiddleName(ui->lineEditMiddleName->text());
    updatedEmployee.setPost(ui->lineEditPost->text());
    updatedEmployee.setSalary(ui->lineEditSalary->text().toDouble());
    updatedEmployee.setLastName(ui->lineEditLastName->text());
    updatedEmployee.setMiddleName(ui->lineEditMiddleName->text());
    updatedEmployee.setAddress(ui->lineEditAddress->text());
    updatedEmployee.setPost(ui->lineEditPost->text());

    // updatedEmployee.setSalary(salary);
    // updatedEmployee.setPremium(premium);

    updatedEmployee.setSalary(ui->lineEditSalary->text().toDouble());
    updatedEmployee.setPremium(ui->lineEditPremium->text().toDouble());

    updatedEmployee.setIdNumber(ui->lineEditIDNumber->text());
    updatedEmployee.setLicenseNumber(ui->lineEditLicenseNumber->text());
    updatedEmployee.setTaxNumber(ui->lineEditTaxNumber->text());
    updatedEmployee.setPensionNumber(ui->lineEditPensionNumber->text());
    updatedEmployee.setSpecialEquipment(ui->lineEditspecialEquipment->text());
    updatedEmployee.setIsGun(ui->checkBoxGun->isChecked());

    updatedEmployee.setGunMark(ui->lineEditGunMark->text());
    updatedEmployee.setGunNumber(ui->lineEditGunNumber->text());
    updatedEmployee.setIsSchedule(ui->checkBoxIsShedule->isChecked());
    // updatedEmployee.setSpecialEquipment(ui->lineEditSpecialEquipment->text());
    // updatedEmployee.setIsGun(ui->checkBoxIsGun->isChecked());
    return updatedEmployee;
}

// void ChangeEmployee::onSaveButtonClicked() {

// }
