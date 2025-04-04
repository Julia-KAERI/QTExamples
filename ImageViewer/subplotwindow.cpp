#include "subplotwindow.hpp"
#include "ui_subplotwindow.h"

SubplotWindow::SubplotWindow(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::SubplotWindow)
{
    ui->setupUi(this);
}

SubplotWindow::~SubplotWindow()
{
    delete ui;
}

void SubplotWindow::load(QString path){
    this->filePath = path;
    cv::Mat cvimg = cv::imread(path.toStdString(), cv::IMREAD_UNCHANGED);
    cv::Mat hist;

    int hist_size[] = {65536};
    float channel_range[] = { 0, 65536 };
    const float* channel_ranges[] = {channel_range};
    const int* channel_numbers = { 0 };
    cv::calcHist(&cvimg, 1, channel_numbers , cv::Mat(), hist, 1, hist_size, channel_ranges);

    for(int i = 0 ; i<hist.rows; i++) this->histdata.append(((float*)hist.data)[i]);

    QImage qimg;
    qimg = QImage(cvimg.data, cvimg.cols, cvimg.rows, QImage::Format_Grayscale16);
    std::cout << "Subwin : " << qimg.pixel(4000, 4000) << ", " << cvimg.at<unsigned short>(4000, 4000) << std::endl;
    this->ui->label->setPixmap(QPixmap::fromImage(qimg));
    return;

}

void SubplotWindow::transform(int rotation, int scale, int contrast){
    QPixmap pxm, pxm2;
    QImage img;
    pxm = this->ui->label->pixmap().copy();
    if (scale < 100){
        int w, h;
        w = int(pxm.width()*(scale)/100.0);
        h = int(pxm.height()*(scale)/100.0);
        pxm = pxm.scaled(w, h, Qt::KeepAspectRatio);
        // std::cout<< "Width from " << pixmap.width() << " to " << w << std::endl;
    }

    if (rotation != 0){
        pxm = pxm.transformed(QTransform().rotate(-(rotation)));
    }



    img = pxm.toImage();

    if (contrast <100){
        // std::cout << "contast = " << this->contrast << std::endl;
        for(int i=0;i<(img.height());i++){
            for(int j=0; j<(img.width()); j++){
                QColor p = img.pixelColor(j, i);
                if ((i== 1000) && (j==1000)) std::cout <<"whoola" << std::endl;
                int red = p.red();
                int green = p.green();
                int blue = p.blue();
                // if (red>MR) MR=red;
                // if (blue>MB) MB=blue;
                // if (green>MG) MG=green;
                red = (int(red*100/contrast) > 255 ) ? 255 : int(red*100/contrast);
                green = (int(green*100/contrast) > 255) ? 255 : int(green*100/contrast);
                blue = (int(blue*100/contrast) > 255) ? 255 : int(blue*100/contrast);
                img.setPixelColor(j, i, QColor(red, green, blue, 255));
                // img.setPixelColor(j, i, QColor(10, 10, 10, 255));
                // if (alpha > M2) M2 = alpha;
            }
        }
    }



    pxm2 = QPixmap::fromImage(img);
    this->ui->label->setPixmap(pxm2);

    return;
}

void SubplotWindow::setPixmap(QPixmap pxm){
    this->ui->label->setPixmap(pxm);
}
