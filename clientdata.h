#ifndef CLIENTDATA_H
#define CLIENTDATA_H

#include <QWidget>

namespace Ui {
class ClientData;
}

class ClientData : public QWidget
{
    Q_OBJECT

public:
    explicit ClientData(QWidget *parent = nullptr);
    void loadEmployees();
    ~ClientData();

private slots:
    void on_pushButtonPay_clicked();

private:
    Ui::ClientData *ui;
};

#endif // CLIENTDATA_H
