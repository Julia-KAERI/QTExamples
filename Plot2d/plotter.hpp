#ifndef PLOTTER_HPP
#define PLOTTER_HPP

#include <QMainWindow>
#include <QPen>
#include "qcustomplot.hpp"

QT_BEGIN_NAMESPACE
namespace Ui {
class Plotter;
}
QT_END_NAMESPACE

class Plotter : public QMainWindow
{
    Q_OBJECT

public:
    Plotter(QWidget *parent = nullptr);
    ~Plotter();

    void addLinePlot(QVector<double> , QVector<double>, QPen);
    void addScatterPlot(QVector<double> , QVector<double>,  QCPScatterStyle);
    void addLog(QString);



private:
    Ui::Plotter *ui;
};
#endif // PLOTTER_HPP
