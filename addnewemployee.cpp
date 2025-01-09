#include <QMessageBox>

#include "addnewemployee.h"
#include "ui_addnewemployee.h"

#include "generalemployee.h"

AddNewEmployee::AddNewEmployee(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::AddNewEmployee)
{
    ui->setupUi(this);
}

AddNewEmployee::~AddNewEmployee()
{
    delete ui;
}

void AddNewEmployee::on_pushButtonAddEmployee_clicked()
{
    Employee *security = new Employee();

    GeneralEmployee *gEmployee = new GeneralEmployee();

    if (ui->lineEditFirstName->text().isEmpty()) {
        QMessageBox::warning(this, "Ошибка ввода", "Введите имя сотрудника.");
        return;
    }
    if (ui->lineEditLastName->text().isEmpty()) {
        QMessageBox::warning(this, "Ошибка ввода", "Введите фамилию сотрудника.");
        return;
    }
    if (ui->lineEditMiddleName->text().isEmpty()) {
        QMessageBox::warning(this, "Ошибка ввода", "Введите отчество сотрудника.");
        return;
    }
    if (ui->lineEditAddress->text().isEmpty()) {
        QMessageBox::warning(this, "Ошибка ввода", "Введите адрес сотрудника.");
        return;
    }
    if (ui->lineEditPost->text().isEmpty()) {
        QMessageBox::warning(this, "Ошибка ввода", "Введите должность сотрудника.");
        return;
    }

    // Проверка числовых полей
    bool ok;
    double salary = ui->lineEditSalary->text().toDouble(&ok);
    if (!ok || salary < 0) {
        QMessageBox::warning(this, "Ошибка ввода", "Введите корректный оклад (число >= 0).");
        return;
    }
    double premium = ui->lineEditPremium->text().toDouble(&ok);
    if (!ok || premium < 0) {
        QMessageBox::warning(this, "Ошибка ввода", "Введите корректную надбавку (число >= 0).");
        return;
    }

    // Проверка других текстовых полей
    if (ui->lineEditIDNumber->text().isEmpty()) {
        QMessageBox::warning(this, "Ошибка ввода", "Введите номер удостоверения.");
        return;
    }
    if (ui->lineEditLicenseNumber->text().isEmpty()) {
        QMessageBox::warning(this, "Ошибка ввода", "Введите номер лицензии.");
        return;
    }
    if (ui->lineEditTaxNumber->text().isEmpty()) {
        QMessageBox::warning(this, "Ошибка ввода", "Введите ИНН.");
        return;
    }
    if (ui->lineEditPensionNumber->text().isEmpty()) {
        QMessageBox::warning(this, "Ошибка ввода", "Введите номер пенсионного удостоверения.");
        return;
    }
    if (ui->lineEditspecialEquipment->text().isEmpty()) {
        QMessageBox::warning(this, "Ошибка ввода", "Введите спецсредства.");
        return;
    }

    // Проверка полей, связанных с оружием
    if (ui->checkBoxGun->isChecked()) {
        if (ui->lineEditGunMark->text().isEmpty()) {
            QMessageBox::warning(this, "Ошибка ввода", "Введите марку оружия.");
            return;
        }
        if (ui->lineEditGunNumber->text().isEmpty()) {
            QMessageBox::warning(this, "Ошибка ввода", "Введите номер оружия.");
            return;
        }
    }

    // Установка данных в объект
    security->setFirstName(ui->lineEditFirstName->text());
    security->setLastName(ui->lineEditLastName->text());
    security->setMiddleName(ui->lineEditMiddleName->text());
    security->setAddress(ui->lineEditAddress->text());
    security->setPost(ui->lineEditPost->text());

    security->setSalary(salary);
    security->setPremium(premium);

    security->setIdNumber(ui->lineEditIDNumber->text());
    security->setLicenseNumber(ui->lineEditLicenseNumber->text());
    security->setTaxNumber(ui->lineEditTaxNumber->text());
    security->setPensionNumber(ui->lineEditPensionNumber->text());
    security->setSpecialEquipment(ui->lineEditspecialEquipment->text());
    security->setIsGun(ui->checkBoxGun->isChecked());

    security->setGunMark(ui->lineEditGunMark->text());
    security->setGunNumber(ui->lineEditGunNumber->text());

    security->setIsSchedule(ui->checkBoxIsShedule->isChecked());

    gEmployee->addEmployee(*security);
    // parent->loadEmployees();
    emit updateTableRequested();

    ui->lineEditFirstName->clear();
    ui->lineEditLastName->clear();
    ui->lineEditMiddleName->clear();
    ui->lineEditAddress->clear();
    ui->lineEditPost->clear();
    ui->lineEditSalary->clear();
    ui->lineEditPremium->clear();
    ui->lineEditIDNumber->clear();
    ui->lineEditLicenseNumber->clear();
    ui->lineEditTaxNumber->clear();
    ui->lineEditPensionNumber->clear();
    ui->lineEditspecialEquipment->clear();
    ui->checkBoxGun->setCheckState(Qt::Unchecked);
    ui->lineEditGunMark->clear();
    ui->lineEditGunNumber->clear();
    ui->checkBoxIsShedule->setCheckState(Qt::Unchecked);
}

