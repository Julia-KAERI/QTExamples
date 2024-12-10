#include "plotter.hpp"
#include "ui_plotter.h"
#include<QString>

QColor PlotColor[] = {QColor(Qt::blue), QColor(Qt::red), QColor(Qt::green), QColor(Qt::cyan), QColor(Qt::black)};
Plotter::Plotter(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Plotter)
{
    ui->setupUi(this);
}

Plotter::~Plotter()
{
    delete ui;
}

void Plotter::addLinePlot(QVector<double> x, QVector<double> y, QPen pen){
    int cnt = this->ui->plt->graphCount();
    auto sv = QString::number(cnt);
    this->ui->log->appendPlainText(QString(sv));
    this->ui->plt->addGraph();
    this->ui->plt->graph(cnt)->setPen(pen);
    this->ui->plt->graph(cnt)->setData(x, y);
    this->ui->plt->graph(cnt)->rescaleAxes(true);
    this->ui->plt->yAxis->scaleRange(1.1, this->ui->plt->yAxis->range().center());
    this->ui->plt->xAxis->scaleRange(1.1, this->ui->plt->xAxis->range().center());
}

void Plotter::addScatterPlot(QVector<double>x, QVector<double> y, QCPScatterStyle sstyle){
    int cnt = this->ui->plt->graphCount();
    auto sv = QString::number(cnt);
    this->ui->log->appendPlainText(QString(sv));
    this->ui->plt->addGraph();
    // this->ui->plt->graph(cnt)->setPen(pen);
    this->ui->plt->graph(cnt)->setData(x, y);
    // this->ui->plt->graph(cnt)->rescaleAxes(true);
    this->ui->plt->graph(cnt)->setScatterStyle(sstyle);
    this->ui->plt->graph(cnt)->rescaleAxes(true);
    this->ui->plt->yAxis->scaleRange(1.1, this->ui->plt->yAxis->range().center());
    this->ui->plt->xAxis->scaleRange(1.1, this->ui->plt->xAxis->range().center());
}
