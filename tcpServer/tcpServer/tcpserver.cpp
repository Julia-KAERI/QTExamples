#include "tcpserver.hpp"
#include "./ui_tcpserver.h"
#include <QHostAddress>
#include <QtNetwork>

// 참고한 사이트
//
// https://coding-chobo.tistory.com/42
//

static inline qint32 ArrayToInt(QByteArray source);

tcpServer::tcpServer(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::tcpServer)
{
    ui->setupUi(this);
}

tcpServer::~tcpServer()
{
    delete ui;
}


void tcpServer::startServer()
{
    QString ipAddress;
    const QList<QHostAddress> ipAddressesList = QNetworkInterface::allAddresses();
    this->ui->plainTextEdit->appendPlainText("start Server");
    mServer=new QTcpServer(this);
    // newConnection 신호 발생시 서버를 newConnection 함수에 연결
    connect(mServer, SIGNAL(newConnection()),this, SLOT(newClient()));

    if(!mServer->listen(QHostAddress::Any, 44444))
    {
        // 서버가 가동이 되지 않으면 메시지 출력
        this->ui->plainTextEdit->appendPlainText("Operation Fail");
        return;
    }

    // 서버가 가동 중이면 start 메시지 출력
    this->ui->plainTextEdit->appendPlainText("Operation Success");


    // use the first non-localhost IPv4 address
    for (const QHostAddress &entry : ipAddressesList) {
        if (entry != QHostAddress::LocalHost && entry.toIPv4Address()) {
            ipAddress = entry.toString();
            break;
        }
    }

    if (ipAddress.isEmpty()) ipAddress = QHostAddress(QHostAddress::LocalHost).toString();


    this->ui->plainTextEdit->appendPlainText(tr("IP address : %1 and port : %2").arg(ipAddress).arg(mServer->serverPort()));
}

void tcpServer::sendMsgToClient()
{
    QByteArray msg;
    QDataStream out(&msg, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_6_5);


    out << this->ui->lineEdit->text();

    // this->ui->plainTextEdit->appendPlainText(this->ui->lineEdit->text());
    QTcpSocket *clientConnection = mServer->nextPendingConnection();
    connect(clientConnection, SIGNAL(readyRead()), this, SLOT(readyToReceive()));
    connect(clientConnection, &QAbstractSocket::disconnected,
            clientConnection, &QObject::deleteLater);
    //! [7] //! [8]

    clientConnection->write(msg);
    clientConnection->disconnectFromHost();
    this->ui->lineEdit->clear();
}

void tcpServer::disconnect()
{
    this->ui->plainTextEdit->appendPlainText("disconnected");
}

void tcpServer::msgReceived(QString)
{
    this->ui->plainTextEdit->appendPlainText("msg Received");
}

// void tcpServer::dataReceived(QString data)
// {
//     ui->plainTextEdit->appendPlainText(data);
// }

void tcpServer::readyToReceive()
{
    QTcpSocket *socket = static_cast<QTcpSocket*>(sender());
    QByteArray *buffer = buffers.value(socket);
    qint32 *s = sizes.value(socket);
    qint32 size = *s;
    while (socket->bytesAvailable() > 0)
    {
        buffer->append(socket->readAll());
        while ((size == 0 && buffer->size() >= 4) || (size > 0 && buffer->size() >= size)) //While can process data, process it
        {
            if (size == 0 && buffer->size() >= 4) //if size of data has received completely, then store it on our global variable
            {
                size = ArrayToInt(buffer->mid(0, 4));
                *s = size;
                buffer->remove(0, 4);
            }

            if (size > 0 && buffer->size() >= size) // If data has received completely, then emit our SIGNAL with the data
            {
                ui->plainTextEdit->appendPlainText(QString(buffer->data()));
                QByteArray data = buffer->mid(0, size);
                buffer->remove(0, size);
                size = 0;
                *s = size;
                emit dataReceived(data);
            }
        }
    }
}
void tcpServer::newClient()
{
    QTcpSocket *clientConnection = mServer->nextPendingConnection();
    connect(clientConnection, &QAbstractSocket::disconnected,
            clientConnection, &QObject::deleteLater);
    connect(clientConnection, SIGNAL(dataReceived), this, SLOT(msgReceived));
    this->ui->plainTextEdit->appendPlainText(tr("Connection : %1 : %2")
                                                 .arg((clientConnection->peerAddress()).toString())
                                                 .arg(clientConnection->peerPort()));
}


qint32 ArrayToInt(QByteArray source)
{
    qint32 temp;
    QDataStream data(&source, QIODevice::ReadWrite);
    data >> temp;
    return temp;
}
