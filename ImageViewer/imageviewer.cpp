#include <iostream>
#include "imageviewer.hpp"
#include "ui_imageviewer.h"
#include "dialog.hpp"


ImageViewer::ImageViewer(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::ImageViewer)
{
    QLabel scaleLabel;
    QFont d2(":/fonts/resources/D2Coding-Ver1.3.2-20180524-all.ttc");
    QFont nm(":/fonts/resources/NanumMyeongjo.ttf");

    scaleLabel.setText("Scale .... ");
    ui->setupUi(this);
    // ui->toolBar->addAction(ui->actionOpen);
    ui->toolBar->addWidget(&scaleLabel);
    ui->toolBar->update();

    this->setFont(nm);
    this->ui->listWidget->setFont(d2);

    this->configDlg = new Dialog(this);
    this->configDlg->setModal(true);

    connect(this->ui->actionOpen, SIGNAL(triggered(bool)), this, SLOT(openDir()));
    connect(this->ui->actionViewOption, SIGNAL(triggered(bool)), this, SLOT(configScale()));
    connect(this->ui->listWidget, SIGNAL(itemDoubleClicked(QListWidgetItem*)), this, SLOT(plotItem(QListWidgetItem*)));
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

void ImageViewer::openDir()
{
    QString dirName;
    dirName = QFileDialog::getExistingDirectory(this,tr("Choose Or Create Directory"),
                                                          "/Volumes/NeutronImage",
                                                        // QFileDialog::ShowDirsOnly|
                                                    QFileDialog::DontResolveSymlinks |QFileDialog::DontUseNativeDialog);

    if (dirName.size() > 0){

        if(this->ui->listWidget->count()>0){
            this->ui->listWidget->clear();
        }

        QDir directory(dirName);
        QStringList fileList = directory.entryList(QStringList() << "*.tif" << "*.TIF", QDir::Files);
        fileList.sort(Qt::CaseInsensitive);
        for(const auto& ff: fileList ){
            // this->ui->plainTextEdit->appendPlainText(ff);
            this->ui->listWidget->addItem(ff);
        }
        this->dataDir = QDir(dirName);
    }
}

void ImageViewer::plotItem(QListWidgetItem* item)
{
    QString itemPath = this->dataDir.absoluteFilePath(item->text());
    QPixmap pixmap, pixmap2;
    QImage img;
    QLabel *lb = new QLabel(this);
    QScrollArea *newsa = new QScrollArea(this);
    uint MM = 0;
    // lb->setMinimumSize(300, 300);
    pixmap.load(itemPath);

    if (this->scale < 100){
        int w, h;
        w = int(pixmap.width()*(this->scale)/100.0);
        h = int(pixmap.height()*(this->scale)/100.0);
        pixmap = pixmap.scaled(w, h, Qt::KeepAspectRatio);
        std::cout<< "Width from " << pixmap.width() << " to " << w << std::endl;
    }

    if (this->rotation != 0){
        pixmap = pixmap.transformed(QTransform().rotate(-(this->rotation)));
    }

    if (this->contrast <100){
        for(int i=0;i<img.height();i++){
            for(int j=0; j<img.width(); j++){
                QRgb p = img.pixel(j, i);
                uint alpha = qAlpha(p);
                uint gray = qGray(p);
                if (gray > MM){
                    MM = gray;
                }
            }
        }
    }
    std::cout << "Maximum pixel value = " << MM << std::endl;

    img = pixmap.toImage();
    std::cout<< "pixel value = "<< img.pixel(1, 1) << std::endl;
    pixmap2 = QPixmap::fromImage(img);
    std::cout<< img.isGrayscale() << ", " << int(img.format())<<std::endl;

    lb->setPixmap(pixmap.scaled(pixmap2.width(), pixmap2.height(), Qt::KeepAspectRatio));
    // lb->setText(QString("Hi bb "));
    std::cout<<img.width() << ", "<<img.height()<< std::endl;
    newsa->setWidget(lb);
    newsa->setWidgetResizable(true);
    newsa->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    newsa->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    // newsa->show();


    QMdiSubWindow *subwin= this->ui->mdiArea->addSubWindow(newsa, Qt::Window);
    // QMdiSubWindow *subwin = new QMdiSubWindow(this);
    // subwin->setWidget(newsa);
    subwin->setWindowTitle(item->text());
    subwin->show();

    // this->ui->mdiArea->tileSubWindows();


    int p = this->ui->mdiArea->subWindowList().size();

    this->ui->plainTextEdit->appendPlainText(QString::number(p));

}

void ImageViewer::configScale()
{
    QList<int> result;
    this->configDlg->setValue(this->rotation, this->scale, this->contrast);
    if(this->configDlg->exec() == QDialog::Accepted)
    {
        result = this->configDlg->getValue();
        this->rotation = result[0];
        this->scale = result[1];
        this->contrast = result[2];
    }
    QString r = QString::number(this->rotation).append(QString(", ")).append(QString::number(this->scale));
    r.append(QString(", ")).append(QString::number(this->contrast));
    this->ui->plainTextEdit->appendPlainText(r);
}
