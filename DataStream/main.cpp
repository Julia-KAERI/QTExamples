#include "mainwindow.hpp"

#include <QApplication>
#include "uinttype.hpp"
#include <iostream>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    unsigned int p = 55242;
    uint24 d = {0, 0, 0};
    fromInt(p, &d);
    std::cout << (unsigned) d.data[0] <<"," << (unsigned) d.data[1] <<"," << (unsigned) d.data[2]<<std::endl;
    int h;
    h = toInt(d);
    std::cout << "p=" << h <<std::endl;
    std::cout <<(p & 0x000000ff) <<std::endl;

    unsigned xx = 33333;
    std::cout << (int) xx<< std::endl;

    return a.exec();
}
