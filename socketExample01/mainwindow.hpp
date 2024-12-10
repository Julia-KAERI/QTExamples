#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>
#include <QTcpServer>
#include <QTcpSocket>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    QTcpServer* mServer;
    QTcpSocket* mClient;

private slots:

    void sendMsgToClient();
    void sendMsgToServer();
    // void clearClientText();
    // void clearServerText();
    // void on_PB_sendToClient_clicked();

    // void on_PB_sendToServer_clicked();

    // void on_pushButton_clicked();

    // void on_PB_clearServerText_clicked();

    // void on_PB_clearClientText_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_HPP
