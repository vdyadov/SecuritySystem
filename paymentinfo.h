#ifndef PAYMENTINFO_H
#define PAYMENTINFO_H

#include <QObject>
#include <QDate>

class PaymentInfo : public QObject
{
    Q_OBJECT
private:
    double price;
    QString docNumber;
    QDate docDate;
public:
    explicit PaymentInfo(QObject *parent = nullptr);

signals:
};

#endif // PAYMENTINFO_H
