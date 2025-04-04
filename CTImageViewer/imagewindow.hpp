#ifndef IMAGEWINDOW_H
#define IMAGEWINDOW_H

#include <QWidget>
#include <opencv2/opencv.hpp>
namespace Ui {
class ImageWindow;
}

class ImageWindow : public QWidget
{
    Q_OBJECT

public:
    QString filePath;
    QVector<float> histdata;
    int rotationAngle = 0;
    int scaleFactor = 100;
    int contrastFactor = 100;


    explicit ImageWindow(QWidget *parent = nullptr);
    ~ImageWindow();
    QPixmap getPixmapFromFile(QString, int, int, int);
    void loadImageFile(QString, int, int, int);
    void transform(int, int, int);
    void rotateImage(int);
    void transformImage(int, int);

private:
    Ui::ImageWindow *ui;
};

#endif // IMAGEWINDOW_H
