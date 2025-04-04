#include "ctimageviewer.hpp"

#include <QApplication>
#include <QFontDatabase>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    CTImageViewer w;

    // font initialization
    QString fm1, fm2;

    int fontfixed = QFontDatabase::addApplicationFont(":/fonts/fonts/D2Coding-Ver1.3.2-20180524-all.ttc");
    if(fontfixed != -1) {
        fm1= QFontDatabase::applicationFontFamilies(fontfixed).at(0);

    }
    int fontmain = QFontDatabase::addApplicationFont(":/fonts/fonts/NanumGothicEco.ttf");
    if(fontmain != -1) {
        fm2 = QFontDatabase::applicationFontFamilies(fontmain).at(0);
    }

    QFont font_main(fm2, 11);
    QFont font_fixed(fm1, 11);


    a.setFont(font_main);
    w.setListWidgetFont(font_fixed);
    w.setPlainTextWidgetFont(font_fixed);
    w.show();
    return a.exec();
}
