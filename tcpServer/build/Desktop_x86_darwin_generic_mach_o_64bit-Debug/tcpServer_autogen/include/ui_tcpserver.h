/********************************************************************************
** Form generated from reading UI file 'tcpserver.ui'
**
** Created by: Qt User Interface Compiler version 6.7.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TCPSERVER_H
#define UI_TCPSERVER_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_tcpServer
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QToolButton *toolButton;
    QHBoxLayout *horizontalLayout_3;
    QPlainTextEdit *plainTextEdit;
    QListView *LB_connectedClients;
    QHBoxLayout *horizontalLayout_2;
    QLineEdit *lineEdit;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *tcpServer)
    {
        if (tcpServer->objectName().isEmpty())
            tcpServer->setObjectName("tcpServer");
        tcpServer->resize(800, 600);
        QFont font;
        font.setFamilies({QString::fromUtf8("Nanum Gothic")});
        tcpServer->setFont(font);
        centralwidget = new QWidget(tcpServer);
        centralwidget->setObjectName("centralwidget");
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setObjectName("verticalLayout");
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        label = new QLabel(centralwidget);
        label->setObjectName("label");
        QFont font1;
        font1.setFamilies({QString::fromUtf8("Nanum Gothic")});
        font1.setPointSize(25);
        font1.setBold(true);
        label->setFont(font1);
        label->setAlignment(Qt::AlignmentFlag::AlignCenter);

        horizontalLayout->addWidget(label);

        toolButton = new QToolButton(centralwidget);
        toolButton->setObjectName("toolButton");
        toolButton->setMinimumSize(QSize(100, 30));
        QFont font2;
        font2.setFamilies({QString::fromUtf8("Nanum Gothic")});
        font2.setPointSize(20);
        toolButton->setFont(font2);

        horizontalLayout->addWidget(toolButton);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        plainTextEdit = new QPlainTextEdit(centralwidget);
        plainTextEdit->setObjectName("plainTextEdit");
        QFont font3;
        font3.setFamilies({QString::fromUtf8("D2Coding")});
        plainTextEdit->setFont(font3);
        plainTextEdit->setReadOnly(true);

        horizontalLayout_3->addWidget(plainTextEdit);

        LB_connectedClients = new QListView(centralwidget);
        LB_connectedClients->setObjectName("LB_connectedClients");
        LB_connectedClients->setFont(font3);

        horizontalLayout_3->addWidget(LB_connectedClients);

        horizontalLayout_3->setStretch(0, 4);
        horizontalLayout_3->setStretch(1, 2);

        verticalLayout->addLayout(horizontalLayout_3);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        lineEdit = new QLineEdit(centralwidget);
        lineEdit->setObjectName("lineEdit");
        lineEdit->setFont(font3);

        horizontalLayout_2->addWidget(lineEdit);


        verticalLayout->addLayout(horizontalLayout_2);

        tcpServer->setCentralWidget(centralwidget);
        statusBar = new QStatusBar(tcpServer);
        statusBar->setObjectName("statusBar");
        tcpServer->setStatusBar(statusBar);

        retranslateUi(tcpServer);
        QObject::connect(toolButton, SIGNAL(clicked()), tcpServer, SLOT(startServer()));
        QObject::connect(lineEdit, SIGNAL(returnPressed()), tcpServer, SLOT(sendMsgToClient()));

        QMetaObject::connectSlotsByName(tcpServer);
    } // setupUi

    void retranslateUi(QMainWindow *tcpServer)
    {
        tcpServer->setWindowTitle(QCoreApplication::translate("tcpServer", "tcpServer", nullptr));
        label->setText(QCoreApplication::translate("tcpServer", "Tcp Server", nullptr));
        toolButton->setText(QCoreApplication::translate("tcpServer", "Start", nullptr));
    } // retranslateUi

};

namespace Ui {
    class tcpServer: public Ui_tcpServer {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TCPSERVER_H
