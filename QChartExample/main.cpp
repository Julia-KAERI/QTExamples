#include "mainwindow.hpp"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    // auto m_chart = new QChart();
    // auto chartView = new QChartView(m_chart);
    // auto mainLayout = new QVBoxLayout();
    // auto m_series = new QLineSeries;
    // auto axisX = new QValueAxis;
    // auto axisY = new QValueAxis;
    // axisX->setRange(0, 100);
    // axisX->setTitleText("X-Axis");
    // axisX->setLabelFormat("%g");
    // axisY->setRange(-1.2, 1.2);
    // axisY->setTitleText("Y-Axis");

    // m_chart->addAxis(axisX, Qt::AlignBottom);
    // m_series->attachAxis(axisX);
    // m_chart->addAxis(axisY, Qt::AlignLeft);
    // m_series->attachAxis(axisY);
    // mainLayout->addWidget(chartView);
    // m_chart->setTitle("Chart Test");
    w.show();
    return a.exec();
}
