#include "mainwindow.hpp"

#include <QApplication>
#include <Eigen/Dense>
#include <matplot/matplot.h>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    using namespace matplot;

    std::vector<double> theta = linspace(0, 2 * pi);
    std::vector<double> x = transform(theta, [](double t) { return cos(t); });
    std::vector<double> y = transform(theta, [](double t) { return sin(t); });
    std::vector<double> z = theta;

    stem3(x, y, z, ":*m");

    show();
    return a.exec();
}
