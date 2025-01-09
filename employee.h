#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include <QObject>

class Employee
{
    // Q_OBJECT
private:
    QString firstName;
    QString lastName;
    QString middleName;
    QString address;
    QString post;
    double salary;
    double premium;
    bool isGun;
    QString gunMark;
    QString gunNumber;
    QString specialEquipment;
    QString idNumber;
    QString licenseNumber;
    QString taxNumber;
    QString pensionNumber;
    bool isSchedule;

public:
    // QList<Schedule> schedule;
    explicit Employee(/*QObject *parent = nullptr*/);
    explicit Employee(QString fName, QString lName, QString mName, QString addr, QString pos, double salary, double premium,
                       bool gun, QString gMark, QString gNum, QString equip, QString idNum, QString licNum, QString taxNum,
                      QString pensNum, bool isSched)
        : firstName(fName), lastName(lName), middleName(mName), address(addr), post(pos), salary(salary), premium(premium), isGun(gun),
        gunMark(gMark), gunNumber(gNum), specialEquipment(equip), idNumber(idNum), licenseNumber(licNum), taxNumber(taxNum),
        pensionNumber(pensNum), isSchedule(isSched){}

    QJsonObject toJson() const;
    Employee fromJson(const QJsonObject &obj);
    void saveToJson(Employee &);

    void setFirstName(QString name);
    void setLastName(QString name);
    void setMiddleName(QString name);
    void setAddress(QString address);
    void setPost(QString post);
    void setSalary(double salary);
    void setPremium(double premium);
    void setIsGun(bool gun);
    void setGunMark(QString mark);
    void setGunNumber(QString number);
    void setSpecialEquipment(QString equipment);
    void setIdNumber(QString number);
    void setLicenseNumber(QString number);
    void setTaxNumber(QString number);
    void setPensionNumber(QString number);
    void setIsSchedule(bool isSched);
    // void setSchedule(QList<Schedule> schedul);

    QString getFirstName() const { return firstName; }
    QString getLastName() const { return lastName; }
    QString getMiddleName() const { return middleName; }
    QString getAddress() const { return address; }
    QString getPost() const { return post; }
    QString getGunMark() const { return gunMark; }
    QString getGunNumber() const { return gunNumber; }
    QString getSpecialEquipment() const { return specialEquipment; }
    QString getIdNumber() const { return idNumber; }
    QString getLicenseNumber() const { return licenseNumber; }
    QString getTaxNumber() const { return taxNumber; }
    QString getPensionNumber() const { return pensionNumber; }

    // Геттеры для числовых полей
    double getSalary() const { return salary; }
    double getPremium() const { return premium; }

    // Геттер для логического поля
    bool getIsGun() const { return isGun; }
    bool getIsSchedule() const { return isSchedule; }
signals:
};

#endif // EMPLOYEE_H
