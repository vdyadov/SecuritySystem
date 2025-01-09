#include "employee.h"
#include "generalemployee.h"

#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>

Employee::Employee(/*QObject *parent*/)
    // : QObject{parent}
{

}

// Employee::Employee(QString fName, QString lName, QString mName, QString addr, QString pos, double salary, double premium,
//                    bool gun, QString gMark, QString gNum, QString equip, QString idNum, QString licNum, QString taxNum, QString pensNum)
//     : firstName(fName), lastName(lName), middleName(mName), address(addr), post(pos), salary(salary), premium(premium), isGun(gun),
//     gunMark(gMark), gunNumber(gNum), specialEquipment(equip), idNumber(idNum), licenseNumber(licNum), taxNumber(taxNum), pensionNumber(pensNum)
// {

// }

QJsonObject Employee::toJson() const
{
    QJsonObject obj;

    obj["firstName"] = firstName;
    obj["lastName"] = lastName;
    obj["middleName"] = middleName;
    obj["address"] = address;
    obj["post"] = post;
    obj["salary"] = salary;
    obj["premium"] = premium;
    obj["isGun"] = isGun;
    obj["gunMark"] = gunMark;
    obj["gunNumber"] = gunNumber;
    obj["specialEquipment"] = specialEquipment;
    obj["idNumber"] = idNumber;
    obj["licenseNumber"] = licenseNumber;
    obj["taxNumber"] = taxNumber;
    obj["pensionNumber"] = pensionNumber;
    obj["isSchedule"] = isSchedule;
    return obj;
}

void Employee::saveToJson(Employee &employee)
{
    // QJsonDocument doc;
    QJsonObject root;
    QJsonArray employeesArray;
    // QString curPath = QDir::currentPath();
    QString filePath = "/Users/vlad_os/study/kursach/SecuritySystem/SecuritySystem/build/employee.json";

    employeesArray.append(employee.toJson());

    root["employees"] = employeesArray;

    QFile file(filePath);
    if (file.open(QIODevice::WriteOnly)) {
        file.write(QJsonDocument(root).toJson());
        file.close();
        qDebug() << "Данные сохранены в файл:" << filePath;
    } else {
        qDebug() << "Ошибка сохранения файла:" << filePath;
    }
}

Employee Employee::fromJson(const QJsonObject &obj) {
    return Employee(
        obj["firstName"].toString(),
        obj["lastName"].toString(),
        obj["middleName"].toString(),
        obj["address"].toString(),
        obj["post"].toString(),
        obj["salary"].toDouble(),
        obj["premium"].toDouble(),
        obj["isGun"].toBool(),
        obj["gunMark"].toString(),
        obj["gunNumber"].toString(),
        obj["specialEquipment"].toString(),
        obj["idNumber"].toString(),
        obj["licenseNumber"].toString(),
        obj["taxNumber"].toString(),
        obj["pensionNumber"].toString(),
        obj["isSchedule"].toBool()
        );
}
// void addEmployee(const Employee &employee) {
//     employees.append(employee);
//     saveToFile();
// }

// void removeEmployee(int index) {
//     if (index >= 0 && index < employees.size()) {
//         employees.removeAt(index);
//         saveToFile();
//     }
// }

// Employee newEmployee(firstName, lastName, middleName, position, salary, false);
// agency->addEmployee(newEmployee);
// loadEmployees();



void Employee::setFirstName(QString name)
{
    Employee::firstName = name;
}
void Employee::setLastName(QString name)
{
    Employee::lastName = name;
}
void Employee::setMiddleName(QString name)
{
    Employee::middleName = name;
}
void Employee::setAddress(QString address)
{
    Employee::address = address;
}
void Employee::setPost(QString post)
{
    Employee::post = post;
}
void Employee::setSalary(double salary)
{
    Employee::salary = salary;
}
void Employee::setPremium(double premium)
{
    Employee::premium = premium;
}
void Employee::setIsGun(bool gun)
{
    Employee::isGun = gun;
}
void Employee::setGunMark(QString mark)
{
    Employee::gunMark = mark;
}
void Employee::setGunNumber(QString number)
{
    Employee::gunNumber = number;
}
void Employee::setSpecialEquipment(QString equipment)
{
    Employee::specialEquipment = equipment;
}
void Employee::setIdNumber(QString number)
{
    Employee::idNumber = number;
}
void Employee::setLicenseNumber(QString number)
{
    Employee::licenseNumber = number;
}
void Employee::setTaxNumber(QString number)
{
    Employee::taxNumber = number;
}
void Employee::setPensionNumber(QString number)
{
    Employee::pensionNumber = number;
}
void Employee::setIsSchedule(bool isSched)
{
    Employee::isSchedule = isSched;
}
