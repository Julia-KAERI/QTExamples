#ifndef CTIMAGEVIEWER_HPP
#define CTIMAGEVIEWER_HPP

#include <QMainWindow>
#include <QFileDialog>
#include <QListWidgetItem>
#include <QMdiSubWindow>
#include <QGraphicsScene>
#include <QPainterPath>
QT_BEGIN_NAMESPACE
namespace Ui {
class CTImageViewer;
}
QT_END_NAMESPACE

class CTImageViewer : public QMainWindow
{
    Q_OBJECT

public:
    QDir dataDir;
    int rotationAngle = 0;
    int scaleFactor = 100;
    int contrastFactor = 100;
    QGraphicsScene* histScene;
    QPainterPath histPath;

    CTImageViewer(QWidget *parent = nullptr);
    ~CTImageViewer();
    void setListWidgetFont(QFont);
    void setPlainTextWidgetFont(QFont);
    void plotHist(QVector<float>);


public slots:
    void openDir();
    void viewImage(QListWidgetItem*);
    void rotateSubwindowImage(QString);
    void transformSubwindowImage();
    void imageSelected(QMdiSubWindow*);
    void setGlobalParameters();
    void changeHistogramScale();

private:
    Ui::CTImageViewer *ui;
};
#endif // CTIMAGEVIEWER_HPP
