#include "imageviewer.hpp"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ImageViewer w;
    a.setFont(w.mainFont);

    w.show();

    // w.setLabelImage();
    // w.updatePlotView();
    return a.exec();
}

