/********************************************************************************
** Form generated from reading UI file 'tcpclient.ui'
**
** Created by: Qt User Interface Compiler version 6.7.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TCPCLIENT_H
#define UI_TCPCLIENT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_tcpClient
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QToolButton *toolButton;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_2;
    QLineEdit *LE_IP;
    QLabel *label_3;
    QLineEdit *LE_port;
    QPlainTextEdit *plainTextEdit;
    QLineEdit *LE_msg;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *tcpClient)
    {
        if (tcpClient->objectName().isEmpty())
            tcpClient->setObjectName("tcpClient");
        tcpClient->resize(800, 600);
        centralwidget = new QWidget(tcpClient);
        centralwidget->setObjectName("centralwidget");
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setObjectName("verticalLayout");
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        label = new QLabel(centralwidget);
        label->setObjectName("label");
        QFont font;
        font.setFamilies({QString::fromUtf8("Nanum Gothic")});
        font.setPointSize(25);
        font.setBold(true);
        label->setFont(font);
        label->setAlignment(Qt::AlignmentFlag::AlignCenter);

        horizontalLayout->addWidget(label);

        toolButton = new QToolButton(centralwidget);
        toolButton->setObjectName("toolButton");
        toolButton->setMinimumSize(QSize(100, 30));
        QFont font1;
        font1.setFamilies({QString::fromUtf8("Nanum Gothic")});
        font1.setPointSize(20);
        toolButton->setFont(font1);

        horizontalLayout->addWidget(toolButton);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName("label_2");

        horizontalLayout_2->addWidget(label_2);

        LE_IP = new QLineEdit(centralwidget);
        LE_IP->setObjectName("LE_IP");

        horizontalLayout_2->addWidget(LE_IP);

        label_3 = new QLabel(centralwidget);
        label_3->setObjectName("label_3");

        horizontalLayout_2->addWidget(label_3);

        LE_port = new QLineEdit(centralwidget);
        LE_port->setObjectName("LE_port");

        horizontalLayout_2->addWidget(LE_port);


        verticalLayout->addLayout(horizontalLayout_2);

        plainTextEdit = new QPlainTextEdit(centralwidget);
        plainTextEdit->setObjectName("plainTextEdit");
        QFont font2;
        font2.setFamilies({QString::fromUtf8("D2Coding")});
        plainTextEdit->setFont(font2);
        plainTextEdit->setReadOnly(true);

        verticalLayout->addWidget(plainTextEdit);

        LE_msg = new QLineEdit(centralwidget);
        LE_msg->setObjectName("LE_msg");
        LE_msg->setFont(font2);

        verticalLayout->addWidget(LE_msg);

        tcpClient->setCentralWidget(centralwidget);
        menubar = new QMenuBar(tcpClient);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 800, 24));
        tcpClient->setMenuBar(menubar);
        statusbar = new QStatusBar(tcpClient);
        statusbar->setObjectName("statusbar");
        tcpClient->setStatusBar(statusbar);

        retranslateUi(tcpClient);
        QObject::connect(toolButton, SIGNAL(clicked()), tcpClient, SLOT(connectToServer()));
        QObject::connect(LE_msg, SIGNAL(returnPressed()), tcpClient, SLOT(sendMsgToServer()));

        QMetaObject::connectSlotsByName(tcpClient);
    } // setupUi

    void retranslateUi(QMainWindow *tcpClient)
    {
        tcpClient->setWindowTitle(QCoreApplication::translate("tcpClient", "tcpClient", nullptr));
        label->setText(QCoreApplication::translate("tcpClient", "Tcp Client", nullptr));
        toolButton->setText(QCoreApplication::translate("tcpClient", "Connect", nullptr));
        label_2->setText(QCoreApplication::translate("tcpClient", "IP", nullptr));
        label_3->setText(QCoreApplication::translate("tcpClient", "Port", nullptr));
    } // retranslateUi

};

namespace Ui {
    class tcpClient: public Ui_tcpClient {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TCPCLIENT_H
