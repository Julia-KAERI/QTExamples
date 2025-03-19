#include <iostream>
#include "imageviewer.hpp"
#include "ui_imageviewer.h"



ImageViewer::ImageViewer(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::ImageViewer)
{



    ui->setupUi(this);
    ui->toolBar->addAction(ui->actionOpen);
    connect(this->ui->actionOpen, SIGNAL(toggled(bool)), this, SLOT(openFile()));

}

ImageViewer::~ImageViewer()
{
    delete ui;
}

void ImageViewer::setLabelText(QString qs)
{
    this->ui->label->setText(qs);
}

void ImageViewer::setLabelImage(QString fp)
{
    QPixmap img;
    if (fp.length() == 0) {
        img.load("/Volumes/NeutronImage/neutron imaging/20221108_CICC/object1/Object1_Step_00613_Image_No_00001.tif");
    }
    else {
        img.load(fp);
    }
    this->ui->label->setPixmap(img.scaled(img.width(), img.height(), Qt::KeepAspectRatio));

    std::cout << img.width() <<", " << img.height() << std::endl;
}

void ImageViewer::openFile()
{
    QString fileName;

    // fileName = QFileDialog::getOpenFileName(this, tr("Open Image"), "/Volumes/NeutronImage", tr("Image Files (*.png *.jpg *.bmp *.tif)"));
    fileName = QFileDialog::getOpenFileName(0, "Open some file", "/Volumes/NeutronImage", QObject::tr("Image Files (*.png *.jpg *.bmp *.tif)"), nullptr, QFileDialog::DontUseNativeDialog);
    this->setLabelImage((fileName));
}
