#ifndef ENTITY_H
#define ENTITY_H

#include <QObject>
#include <QDate>

#include "paymentinfo.h"

class Entity
{
protected:
    QString personalAddres;
    QString contractNumber;
    QDate contractDate;
    QString eventName;
    QString eventAddres;
    QDate eventtDate;
    QTime eventTime;
    double price;
    QString paymentDocNum;
    QDate paymentDate;

public:
    explicit Entity();

    // Геттеры
    QString getPersonalAddres() const { return personalAddres; }
    QString getContractNumber() const { return contractNumber; }
    QDate getContractDate() const { return contractDate; }
    QString getEventName() const { return eventName; }
    QString getEventAddres() const { return eventAddres; }
    QDate getEventtDate() const { return eventtDate; }
    QTime getEventTime() const { return eventTime; }
    double getPrice() const { return price; }
    QString getPaymentDocNum() const { return paymentDocNum; }
    QDate getPaymentDate() const { return paymentDate; }

    // Сеттеры
    void setPersonalAddres(const QString &address) { personalAddres = address; }
    void setContractNumber(const QString &number) { contractNumber = number; }
    void setContractDate(const QDate &date) { contractDate = date; }
    void setEventName(const QString &name) { eventName = name; }
    void setEventAddres(const QString &address) { eventAddres = address; }
    void setEventtDate(const QDate &date) { eventtDate = date; }
    void setEventTime(const QTime &time) { eventTime = time; }
    void setPrice(const double &summ) { price = summ; }
    void setPaymentDocNum(const QString &number) { paymentDocNum = number; }
    void setPaymentDate(const QDate &date) { paymentDate = date; }

signals:
};

#endif // ENTITY_H
