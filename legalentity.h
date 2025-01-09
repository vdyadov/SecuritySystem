#ifndef LEGALENTITY_H
#define LEGALENTITY_H

#include <QWidget>
#include "entity.h"

namespace Ui {
class LegalEntity;
}

class LegalEntity : public QWidget, public Entity
{
    Q_OBJECT

public:
    explicit LegalEntity(QWidget *parent = nullptr);
    void loadEmployees();
    void onChangeEmployeeClicked(int i);
    ~LegalEntity();

private slots:
    void on_pushButtonSchedule_clicked();

    void on_pushButtonPayment_clicked();

private:
    QString name;
    QDate contractDateEnd;
    Ui::LegalEntity *ui;
};

#endif // LEGALENTITY_H
