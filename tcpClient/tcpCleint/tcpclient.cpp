#include "tcpclient.hpp"
#include "./ui_tcpclient.h"

tcpClient::tcpClient(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::tcpClient)
    ,tcpSocket(new QTcpSocket(this))
{
    ui->setupUi(this);
}

tcpClient::~tcpClient()
{
    delete ui;
}

void tcpClient::connectToServer()
{
    auto _ip = this->ui->LE_IP->text();
    auto _port = (this->ui->LE_port->text()).toInt();
    tcpSocket->connectToHost(_ip,_port);

    this->ui->plainTextEdit->appendPlainText(tr("IP = %1, port = %2").arg(_ip).arg(_port));
}

void tcpClient::sendMsgToServer()
{
    auto msg = this->ui->LE_msg->text();
    this->ui->plainTextEdit->appendPlainText(tr("[Msg to Server] %1").arg(msg));
    this->ui->LE_msg->clear();
}
