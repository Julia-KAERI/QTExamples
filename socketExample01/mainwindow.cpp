#include "mainwindow.hpp"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    mClient = new QTcpSocket();
    mServer = new QTcpServer();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::sendMsgToClient()
{
    this->ui->PTE_client->appendPlainText(this->ui->LE_serverInput->text());
    this->ui->LE_serverInput->clear();
}


void MainWindow::sendMsgToServer()
{
    this->ui->PTE_server->appendPlainText(this->ui->LE_clientInput->text());
    this->ui->LE_clientInput->clear();
}



// void MainWindow::clearClientText()
// {
//     // this->ui->PTE_server->clear();
//     this->ui->PTE_client->appendPlainText(this->ui->LE_serverInput->text());
// }


// void MainWindow::clearServerText()
// {
//     // this->ui->PTE_client->clear();
//     this->ui->PTE_server->appendPlainText(this->ui->LE_clientInput->text());
// }

