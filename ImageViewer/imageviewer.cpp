#include <iostream>
#include "imageviewer.hpp"
#include "ui_imageviewer.h"



ImageViewer::ImageViewer(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::ImageViewer)
{
    QLabel scaleLabel;
    scaleLabel.setText("Scale .... ");
    ui->setupUi(this);
    // ui->toolBar->addAction(ui->actionOpen);
    ui->toolBar->addWidget(&scaleLabel);
    ui->toolBar->update();
    connect(this->ui->actionOpen, SIGNAL(triggered(bool)), this, SLOT(openFile()));
    this->ui->splitter->setSizes(QList<int>({200, 700}));
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
    QString dirName;
    dirName = QFileDialog::getExistingDirectory(this,tr("Choose Or Create Directory"),
                                                          "/Volumes/NeutronImage",
                                                        QFileDialog::ShowDirsOnly| QFileDialog::DontResolveSymlinks |QFileDialog::DontUseNativeDialog);
    // fileName = QFileDialog::getOpenFileName(this, tr("Open Image"), "/Volumes/NeutronImage", tr("Image Files (*.png *.jpg *.bmp *.tif)"));
    // fileName = QFileDialog::getOpenFileName(0, "Open some file", "/Volumes/NeutronImage", QObject::tr("Image Files (*.png *.jpg *.bmp *.tif)"), nullptr, QFileDialog::DontUseNativeDialog);
    // this->setLabelImage((fileName));
    if (dirName.size() > 0){
        this->ui->plainTextEdit->appendPlainText(dirName);
        this->ui->plainTextEdit->appendPlainText(QString::number(dirName.size()));
        QDir directory(dirName);
        QStringList fileList = directory.entryList(QStringList() << "*.tif" << "*.TIF",QDir::Files);
        for(const auto& ff: fileList ){
            this->ui->plainTextEdit->appendPlainText(ff);
        }
    }
}
