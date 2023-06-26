#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "theatre.h"
#include "playbill_dialog.h"
#include "audience_dialog.h"
#include "troupe_dialog.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ad = new audience_dialog;
    pd = new playbill_dialog;
    td = new troupe_dialog;
    //связываем сигнал и слот новой формы, который будет принимать данные
    connect(this, SIGNAL(sendData(theatre*)), ad, SLOT(recieveData(theatre*)));
    connect(this, SIGNAL(sendData(theatre*)), pd, SLOT(recieveData(theatre*)));
    connect(this, SIGNAL(sendData(theatre*)), td, SLOT(recieveData(theatre*)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_Playbill_clicked()
{
    pd->show();
    emit sendData(Theatre); // сигнал для передачи данных на другую форму
}

void MainWindow::on_Troupe_clicked()
{
    td->show();
    emit sendData(Theatre); // сигнал для передачи данных на другую форму
}

void MainWindow::on_Audience_clicked()
{
    ad->show();
    emit sendData(Theatre); // сигнал для передачи данных на другую форму
}
