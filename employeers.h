#ifndef EMPLOYEERS_H
#define EMPLOYEERS_H

#include <QWidget>



namespace Ui {
class Employeers;
}

class Employeers : public QWidget
{
    Q_OBJECT

public:
    explicit Employeers(QWidget *parent = nullptr);
    ~Employeers();
    void loadEmployees();

private slots:
    void on_pushButtonAddEmployee_clicked();
    void on_pushButtonSchedule_clicked();
    void onChangeEmployeeClicked(int index);
    // void onAddEmployee();
    // void onRemoveEmployee();

private:
    Ui::Employeers *ui;
};

#endif // EMPLOYEERS_H
