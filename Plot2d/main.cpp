#include "plotter.hpp"

#include <QApplication>
#include "qcustomplot.hpp"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Plotter w;
    QVector<double> x1(100), y1(100), y2(100);
    for (int i=0;i<100;i++){
        x1[i] = i;
        y1[i] = 40.0*qSin(i*0.1)+30.0;
        y2[i] = 100.0*qExp(-(i-30)*(i-30)/1000.0);
    }
    w.addLinePlot(x1, y1, QPen(Qt::blue, 4));
    w.addScatterPlot(x1, y2, QCPScatterStyle(QCPScatterStyle::ssCircle, QColor(Qt::red), QColor(Qt::red), 10));
    w.show();
    return a.exec();
}
