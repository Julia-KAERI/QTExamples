#include "imageviewer.hpp"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ImageViewer w;

    w.show();
    // w.setLabelText(QString("ab"));
    w.setLabelImage();

    return a.exec();
}

