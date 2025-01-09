#include "generalemployee.h"

GeneralEmployee::GeneralEmployee() {
    loadFromFile();
}

void GeneralEmployee::saveToFile() const {
    QFile file(filePath);
    if (file.open(QIODevice::WriteOnly)) {
        QJsonObject root;
        QJsonArray employeesArray;
        for (auto const &employee : employees) {
            QJsonObject employeeJson = employee.toJson();
            employeesArray.append(QJsonValue(employeeJson));
        }
        root["employees"] = employeesArray;

        file.write(QJsonDocument(root).toJson());
        file.close();
    }
}

void GeneralEmployee::saveToFileOneEmployee() const {
    QFile file(filePathPay);
    if (file.open(QIODevice::WriteOnly)) {
        QJsonObject root;
        QJsonArray employeesArray;
        for (auto const &employee : employeesPay) {
            QJsonObject employeeJson = employee.toJson();
            employeesArray.append(QJsonValue(employeeJson));
        }
        root["employeesPay"] = employeesArray;

        file.write(QJsonDocument(root).toJson());
        file.close();
    }
}

void GeneralEmployee::saveToFileDelEmployee() const {
    QFile file(filePathDel);
    if (file.open(QIODevice::WriteOnly)) {
        QJsonObject root;
        QJsonArray employeesArray;
        for (auto const &employee : employeesDel) {
            QJsonObject employeeJson = employee.toJson();
            employeesArray.append(QJsonValue(employeeJson));
        }
        root["employeesDel"] = employeesArray;

        file.write(QJsonDocument(root).toJson());
        file.close();
    }
}

void GeneralEmployee::addEmployee(Employee &employee) {
    // auto employeePtr = std::make_shared<Employee>();
    employees.append(employee);
    saveToFile();
}

void GeneralEmployee::loadFromFile() {
    QFile file(filePath);
    Employee *employee = new Employee();
    if (file.open(QIODevice::ReadOnly)) {
        QByteArray data = file.readAll();
        file.close();

        QJsonDocument doc = QJsonDocument::fromJson(data);
        QJsonObject root = doc.object();

        employees.clear();
        QJsonArray employeesArray = root["employees"].toArray();
        for (const auto &employeeValue : employeesArray) {
            employees.append(employee->fromJson(employeeValue.toObject()));
        }
    }
}

void GeneralEmployee::loadFromFileOneEmployee() {
    QFile file(filePathPay);
    Employee *employee = new Employee();
    if (file.open(QIODevice::ReadOnly)) {
        QByteArray data = file.readAll();
        file.close();

        QJsonDocument doc = QJsonDocument::fromJson(data);
        QJsonObject root = doc.object();

        employeesPay.clear();
        QJsonArray employeesArray = root["employeesPay"].toArray();
        for (const auto &employeeValue : employeesArray) {
            employeesPay.append(employee->fromJson(employeeValue.toObject()));
        }
    }
}
void GeneralEmployee::loadFromFileDelEmployee() {
    QFile file(filePathDel);
    Employee *employee = new Employee();
    if (file.open(QIODevice::ReadOnly)) {
        QByteArray data = file.readAll();
        file.close();

        QJsonDocument doc = QJsonDocument::fromJson(data);
        QJsonObject root = doc.object();

        employeesDel.clear();
        QJsonArray employeesArray = root["employeesDel"].toArray();
        for (const auto &employeeValue : employeesArray) {
            employeesDel.append(employee->fromJson(employeeValue.toObject()));
        }
    }
}

void GeneralEmployee::removeEmployee(int index) {
    if (index >= 0 && index < employees.size()) {
        employees.removeAt(index);
        saveToFile();
    }
}

void GeneralEmployee::updateEmployee(int index, const Employee &updatedEmployee) {
    if (index >= 0 && index < employees.size()) {
        employees[index] = updatedEmployee; // Обновляем запись в коллекции
        saveToFile(); // Сохраняем изменения в файл
    }
}

const QList<Employee> &GeneralEmployee::getEmployees() const {
    return employees;
}

const QList<Employee> &GeneralEmployee::getEmployeesIsSched() const {
    QList<Employee> *validEmployees = new QList<Employee>();
    for (auto employeesIsSchedule : employees)
    {
        if (employeesIsSchedule.getIsSchedule())
        {
            validEmployees->append(employeesIsSchedule);
        }
    }

    return *validEmployees;
}
