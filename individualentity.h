#ifndef INDIVIDUALENTITY_H
#define INDIVIDUALENTITY_H

#include <QWidget>

namespace Ui {
class IndividualEntity;
}

class IndividualEntity : public QWidget
{
    Q_OBJECT

public:
    explicit IndividualEntity(QWidget *parent = nullptr);
    void loadEmployees();
    void onChangeEmployeeClicked(int i);
    ~IndividualEntity();

private slots:
    void on_pushButtonPayment_clicked();

private:
    Ui::IndividualEntity *ui;
};

#endif // INDIVIDUALENTITY_H
