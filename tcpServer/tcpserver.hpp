#ifndef TCPSERVER_HPP
#define TCPSERVER_HPP

#include <QMainWindow>
#include <QTcpServer>
#include <QtNetwork>
#include <QString>
#include <QtCore>

QT_BEGIN_NAMESPACE
namespace Ui {
class tcpServer;
}
QT_END_NAMESPACE

class tcpServer : public QMainWindow
{
    Q_OBJECT

public:
    tcpServer(QWidget *parent = nullptr);
    ~tcpServer();

    void waitConnection();
    QTcpServer* mServer = nullptr;

private:

signals:
    void dataReceived(QByteArray);

private slots:
    void startServer();
    void sendMsgToClient();
    void newClient();
    void msgReceived(QString);
    // void dataReceived(QString);
    void disconnect();
    void readyToReceive();

private:
    Ui::tcpServer *ui;
    QTcpSocket *clientConnection = nullptr;
    QHash<QTcpSocket*, QByteArray*> buffers; //We need a buffer to store data until block has completely received
    QHash<QTcpSocket*, qint32*> sizes;
};
#endif // TCPSERVER_HPP
