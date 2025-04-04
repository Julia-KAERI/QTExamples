#ifndef IMAGEVIEWER_HPP
#define IMAGEVIEWER_HPP

#include <QMainWindow>
#include <QFileDialog>
#include <QLabel>
#include <QPixmap>
#include <QFont>
#include <QListWidgetItem>
#include <QMdiArea>
#include <QMdiSubWindow>
#include <QRgb>
#include <QColor>
#include <QFontDatabase>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QString>
#include <QGraphicsRectItem>
#include <QPainterPath>
#include "dialog.hpp"
#include "histview.hpp"
#include <opencv2/opencv.hpp>

QT_BEGIN_NAMESPACE
class QLabel;
namespace Ui {
class ImageViewer;

}
QT_END_NAMESPACE

class ImageViewer : public QMainWindow
{
    Q_OBJECT

public slots:
    void openDir();
    void plotItem(QListWidgetItem*);
    void configScale();
    void updatePanel(QMdiSubWindow*);
    void updateHistogram();
public:
    QDir dataDir;
    Dialog *configDlg;
    QFont mainFont;
    QGraphicsScene *plotScene;
    QGraphicsRectItem * plotBorder;
    HistView *plotView;
    int rotation=0;
    int scale=100;
    int contrast=100;
    ImageViewer(QWidget *parent = nullptr);
    // void setLabelText(QString);
    // void setLabelImage(QString fp = QString(""));
    void updatePlotView();
    void plotHistogram();
    ~ImageViewer();


    Ui::ImageViewer *ui;
private:
};

#endif // IMAGEVsIEWER_HPP

