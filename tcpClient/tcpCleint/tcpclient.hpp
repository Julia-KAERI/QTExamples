#ifndef TCPCLIENT_HPP
#define TCPCLIENT_HPP

#include <QMainWindow>
#include <QTcpSocket>

QT_BEGIN_NAMESPACE
namespace Ui {
class tcpClient;
}
QT_END_NAMESPACE

class tcpClient : public QMainWindow
{
    Q_OBJECT

public:
    tcpClient(QWidget *parent = nullptr);
    ~tcpClient();

private:
    Ui::tcpClient *ui;
    QTcpSocket *tcpSocket = nullptr;

private slots:
    void connectToServer();
    void sendMsgToServer();
};


#endif // TCPCLIENT_HPP
