#include "imagewindow.hpp"
#include "ui_imagewindow.h"
#include <QTest>
ImageWindow::ImageWindow(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ImageWindow)
{
    ui->setupUi(this);
}

ImageWindow::~ImageWindow()
{
    delete ui;
}


QPixmap ImageWindow::getPixmapFromFile(QString filePath, int rotation, int scale, int contrast){
    QPixmap pxm;
    cv::Mat cvimg = cv::imread(filePath.toStdString(), cv::IMREAD_UNCHANGED);
    cv::Mat hist;
    QImage qimg;

    int hist_size[] = {65536};
    float channel_range[] = { 0, 65536 };
    const float* channel_ranges[] = {channel_range};
    const int* channel_numbers = { 0 };
    cv::calcHist(&(cvimg), 1, channel_numbers , cv::Mat(), hist, 1, hist_size, channel_ranges);

    for(int i = 0 ; i<(hist.rows); i++) histdata.append(((float*)hist.data)[i]);

    if(scale < 100) cv::resize(cvimg, cvimg, cv::Size(int(cvimg.cols*scale/100), int(cvimg.rows*scale/100) ));
    if(contrast < 100) cvimg.convertTo(cvimg, -1, 100/float(contrast), 0.0);


    qimg = QImage(cvimg.data, cvimg.cols, cvimg.rows, QImage::Format_Grayscale16);
    pxm = QPixmap::fromImage(qimg);
    if(rotation!=0) pxm = pxm.transformed(QTransform().rotate(-(rotation)));
    return pxm;
}

void ImageWindow::loadImageFile(QString filePath, int rotation, int scale, int contrast){
    this->filePath = filePath;
    QPixmap pxm = this->getPixmapFromFile(filePath, rotation, scale, contrast);
    this->ui->imageLabel->setPixmap(pxm);
    return;
}

void ImageWindow::transform(int rotation, int scale, int contrast){

}

void ImageWindow::rotateImage(int rotation){
    if(this->rotationAngle != rotation){
        QPixmap pixmap = this->ui->imageLabel->pixmap();
        pixmap = pixmap.transformed(QTransform().rotate(-(rotation-this->rotationAngle)));
        this->ui->imageLabel->setPixmap(pixmap);
        this->rotationAngle = rotation;
    }

}


void ImageWindow::transformImage(int scale, int contrast){
    if(this->scaleFactor != scale || this->contrastFactor != contrast){

        cv::Mat cvimg = cv::imread((this->filePath).toStdString(), cv::IMREAD_UNCHANGED);

        QImage qimg;
        std::cout << "original size = " << cvimg.cols << ", " << cvimg.rows << std::endl;
        cv::resize(cvimg, cvimg, cv::Size(), double(scale)/100, double(scale)/100);
        // cvimg.convertTo(cvimg, -1, 100/float(contrast), 0.0);
        std::cout << "transposed size = " << cvimg.cols << ", " << cvimg.rows << std::endl;
        cvimg.convertTo(cvimg, CV_8U, 100/float(contrast)/257.0, 0.0);
        // std::cout << "OpenCV mat type : " << cvimg.type() << std::endl;
        // cv::namedWindow("image"); // 이미지를 보여주기 위한 빈 창
        // cv::imshow("image", cvimg);
        // cv::waitKey();
        // QTest::qWait(100);
        qimg = QImage(cvimg.data, cvimg.cols, cvimg.rows, static_cast<int>(cvimg.step), QImage::Format_Grayscale8);
        std::cout << "Qimage size " << qimg.width() <<", " << qimg.height() << std::endl;
        QPixmap pxm = QPixmap::fromImage(qimg, Qt::MonoOnly);
        // pxm.transformed(QTransform().rotate(-(this->rotationAngle)));
        this->ui->imageLabel->setPixmap(pxm);
        this->contrastFactor = contrast;
        this->scaleFactor = scale;
    }

}



