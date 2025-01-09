#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "ui_employeers.h"
#include "employeers.h"

#include "individualentity.h"
#include "legalentity.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButtonAdmin_clicked()
{
    Employeers *manageEmployeers = new Employeers();
    manageEmployeers->show();
}


void MainWindow::on_pushButtonIndividualEntity_clicked()
{
    IndividualEntity *individualEntity = new IndividualEntity();
    individualEntity->show();
}


void MainWindow::on_pushButtonLegalEntity_clicked()
{
    LegalEntity *legalEntity = new LegalEntity();
    // legalEmployeers->ui->pushButton->setText("Посмотреть выбранные услуги");
    // legalEmployeers->ui->pushButton_2->setText("Оформить заказ");
    legalEntity->show();
}

