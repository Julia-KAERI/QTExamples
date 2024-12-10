
#include "mainwindow.hpp"
#include "./ui_mainwindow.h"
#include "widget.h"
#include <QChart>
#include <QChartView>
#include <QLineSeries>
#include <QValueAxis>
#include <QVBoxLayout>
#include <QLineSeries>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    auto mainLayout = new QVBoxLayout();
    ui->setupUi(this);
    auto m_chart = new QChart();
    auto m_series = new QLineSeries();
    *m_series << QPointF(1, 5) << QPointF(3, 7) << QPointF(7, 6) << QPointF(9, 7)
              << QPointF(12, 6) << QPointF(16, 7) << QPointF(18, 5);
    auto chartView = new QChartView(m_chart);
    m_chart->addSeries(m_series);
    auto axisX = new QValueAxis;
    axisX->setRange(0, 20);
    axisX->setLabelFormat("%g");
    axisX->setTitleText("Samples");
    auto axisY = new QValueAxis;
    axisY->setRange(-1, 15);
    axisY->setTitleText("Audio level");
    m_chart->addAxis(axisX, Qt::AlignBottom);
    m_series->attachAxis(axisX);
    m_chart->addAxis(axisY, Qt::AlignLeft);
    m_series->attachAxis(axisY);
    m_chart->legend()->hide();
    m_chart->setTitle("Title");
    // *m_series << QPointF(1, 5) << QPointF(3, 7) << QPointF(7, 6) << QPointF(9, 7)
    //         << QPointF(12, 6) << QPointF(16, 7) << QPointF(18, 5);
    this->ui->verticalLayout_2->addWidget(chartView);



    // this->ui->verticalLayout_2->addWidget(w);
    // mainLayout->addWidget(w);
}

MainWindow::~MainWindow()
{
    delete ui;
}
