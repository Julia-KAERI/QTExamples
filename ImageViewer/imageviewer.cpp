#include <QDebug>
#include <iostream>
#include "imageviewer.hpp"
#include "ui_imageviewer.h"
#include "dialog.hpp"
#include "subplotwindow.hpp"

ImageViewer::ImageViewer(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::ImageViewer)
{
    QLabel scaleLabel;
    // QFont d2(":/fonts/resources/D2Coding-Ver1.3.2-20180524-all.ttc");
    // QFont nm(":/fonts/resources/NanumMyeongjo.ttf");
    QString fm1, fm2;

    this->plotScene = new QGraphicsScene();
    // font loading
    int fontid1 = QFontDatabase::addApplicationFont(":/fonts/resources/D2Coding-Ver1.3.2-20180524-all.ttc");
    if(fontid1 != -1) {
        fm1= QFontDatabase::applicationFontFamilies(fontid1).at(0);

    }
    int fontid2 = QFontDatabase::addApplicationFont(":/fonts/resources/NanumGothicEco.ttf");
    if(fontid2 != -1) {
        fm2 = QFontDatabase::applicationFontFamilies(fontid2).at(0);
    }

    QFont d2(fm1, 11);
    this->mainFont = QFont(fm2, 11);

    // this->setFont(nm);
    // this->ui->listWidget->setFont(d2);

    scaleLabel.setText("Scale .... ");
    ui->setupUi(this);
    // ui->toolBar->addAction(ui->actionOpen);
    ui->toolBar->addWidget(&scaleLabel);
    ui->toolBar->update();

    // this->setFont(nm);
    this->ui->listWidget->setFont(d2);

    this->configDlg = new Dialog(this);
    this->configDlg->setModal(true);

    // this->ui->splitter->setStretchFactor(0, 1);
    // this->ui->splitter->setStretchFactor(1, 4);
    // this->ui->splitter->setStretchFactor(2, 1);

    plotView = this->ui->plotView;
    this->ui->splitter->setSizes(QList<int>({150, 700, 150}));
    int wp = this->ui->plotView->width();
    int hp = this->ui->plotView->height();

    std::cout << "width=" << wp <<", height = "<<hp<<std::endl;

    this->ui->plotView->setScene(this->plotScene);
    this->ui->plotView->fitInView(this->ui->plotView->sceneRect());
    this->plotBorder = this->plotScene->addRect(QRect(5.0, 5.0, 155.0, 155.0), QPen(Qt::white), QBrush(1));

    connect(this->ui->actionOpen, SIGNAL(triggered(bool)), this, SLOT(openDir()));
    connect(this->ui->actionViewOption, SIGNAL(triggered(bool)), this, SLOT(configScale()));
    connect(this->ui->listWidget, SIGNAL(itemDoubleClicked(QListWidgetItem*)), this, SLOT(plotItem(QListWidgetItem*)));
    connect(this->ui->mdiArea, SIGNAL(subWindowActivated(QMdiSubWindow*)), this, SLOT(updatePanel(QMdiSubWindow*)));
    // connect(this->plotScene, SIGNAL(sceneRectChanged(QRectF)), this, SLOT(updateHistogram()));
    // connect(this->ui->plotView, SIGNAL(sizeChanged()), this, SLOT(updatePlot()));

    // delete this->configDlg;
}


ImageViewer::~ImageViewer()
{
    delete ui;
}

// void ImageViewer::setLabelText(QString qs)
// {
//     this->ui->label->setText(qs);
// }

// void ImageViewer::setLabelImage(QString fp)
// {
//     QPixmap img;
//     SubplotWindow* subwin = new SubplotWindow(this);

//     if (fp.length() == 0) {
//         img.load("/Volumes/NeutronImage/neutron imaging/20221108_CICC/object1/Object1_Step_00613_Image_No_00001.tif");
//         QImage qimg = img.toImage();
//         std::cout << "Format : " << qimg.format() << std::endl;
//     }
//     else {
//         img.load(fp);
//     }
//     // this->ui->label->setPixmap(img.scaled(img.width(), img.height(), Qt::KeepAspectRatio));

//     subwin->setPixmap(img);
//     this->ui->mdiArea->addSubWindow(subwin);
//     subwin->setWindowTitle("item->text()");
//     subwin->show();

//     std::cout << img.width() <<", " << img.height() << std::endl;
// }

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

    // ImageViewer->ui->mdiArea 에 이미 그려져 있는 데이터를 선택할 경우
    // 그냥 패스한다.
    QList<QMdiSubWindow *> subwindowlist = this->ui->mdiArea->subWindowList();

    for(QMdiSubWindow *p: subwindowlist){
        if (p->windowTitle() == item->text())
        {
            return ;
        }
    }

    // Imageviwer->ui->mdiArea 에 이미 그려져 있는 데이터가 아닌 경우

    QString itemPath = this->dataDir.absoluteFilePath(item->text());

    SubplotWindow* subwins = new SubplotWindow(this);
    subwins->load(itemPath);
    this->ui->mdiArea->addSubWindow(subwins);
    subwins->setWindowTitle(item->text());
    subwins->show();
    subwins->transform(this->rotation, this->scale, this->contrast);

    this->ui->plotView->plotHistogram(&(subwins->histdata));
    return;

    // QPixmap pixmap, pixmap2;
    // QImage img, pimg;
    // QLabel *lb = new QLabel(this);
    // QScrollArea *newsa = new QScrollArea(this);
    // plotView = this->ui->plotView;
    // int MR{0}, MG{0}, MB{0};
    // // lb->setMinimumSize(300, 300);
    // pixmap.load(itemPath);
    // pimg.load(itemPath);
    // cv::Mat cvimg = cv::imread(itemPath.toStdString(), cv::IMREAD_UNCHANGED);

    // double minVal;
    // double maxVal;
    // cv::Point minLoc;
    // cv::Point maxLoc;

    // minMaxLoc( cvimg, &minVal, &maxVal, &minLoc, &maxLoc );

    // std::cout << "min val: " << minVal << std::endl;
    // std::cout << "max val: " << maxVal << std::endl;

    // cv::Mat hist;
    // int hist_size[] = {65526};
    // float channel_range[] = { 0.0, 65525.0 };
    // const float* channel_ranges[] = {channel_range};
    // const int* channel_numbers = { 0 };
    // cv::calcHist(&cvimg, 1, channel_numbers , cv::Mat(), hist, 1, hist_size, channel_ranges);

    // minMaxLoc( hist, &minVal, &maxVal, &minLoc, &maxLoc );
    // std::cout << "hist : min val: " << minVal << " at " << "(" << minLoc.x<< ", " << minLoc.y << ")" << std::endl;
    // std::cout << "hist : max val: " << maxVal << " at " << "(" << maxLoc.x<< ", " << maxLoc.y << ")" << std::endl;
    // std::cout << "OpenCV Image, cols = " << cvimg.cols << ", rows = " << cvimg.rows <<", depth = " << cvimg.depth() <<", channels = " << cvimg.channels() << ", type = " <<cvimg.type() << std::endl;
    // std::cout << "Histogram cols = " << hist.cols << ", rows = " <<hist.rows <<", depth = " << hist.depth() << ", channels = " << hist.channels() << ", type = " << hist.type() << ", " <<hist.at<float>(1, 1) << std::endl;
    // this->ui->plainTextEdit->appendPlainText(QString::number(pimg.pixel(1,1)));

    // QPainterPath plotPath;


    // qreal rx, ry, rw, rh;
    // // this->plotBorder->rect().getRect(&rx, &ry, &rw, &rh);

    // this->ui->plainTextEdit->appendPlainText(QString("Rect : ") + QString::number(rx) + QString(", ")  + QString::number(ry) );
    // qreal MM, mm;
    // MM = 0.0;
    // mm = 100;
    // qreal xstep = rw*0.9/hist.rows;
    // qreal ystep = rh*0.9/maxVal;
    // // qreal ystep = rh*0.9/500;
    // qreal x0 = rx+rw*0.05;
    // qreal y0 = ry+rh*0.05;

    // qreal hx, hy;

    // for(int i = 0 ; i<hist.rows; i++){
    //     float data = ((float*)hist.data)[i];


    //     hx = x0+i*xstep;
    //     hy =  rh - (y0 + data*ystep);
    //     if (data>MM) MM = data;
    //     if (data<mm) mm = data;
    //     if(i==0) plotPath.moveTo(hx, hy);
    //     else {

    //         plotPath.lineTo(hx, hy);
    //     }
    // }
    // // plotPath.closeSubpath();
    // this->ui->plainTextEdit->appendPlainText(QString("Maximum and minimum position of histogram") + QString::number(MM) + QString(", ") + QString::number(mm) );

    // QGraphicsPathItem* ps;
    // ps = this->plotScene->addPath(plotPath, QPen(Qt::yellow), QBrush(1));
    // ps->setVisible(true);
    // ps->show();
    // this->ui->plainTextEdit->appendPlainText(QString("Path length : ") + QString::number(plotPath.length()));
    // this->plotScene->addLine( 30, 30, 80, 80, QPen(Qt::yellow));
    // // std::cout << "Image Format " <<pimg.format() << std::endl;

    // if (this->scale < 100){
    //     int w, h;
    //     w = int(pixmap.width()*(this->scale)/100.0);
    //     h = int(pixmap.height()*(this->scale)/100.0);
    //     pixmap = pixmap.scaled(w, h, Qt::KeepAspectRatio);
    //     std::cout<< "Width from " << pixmap.width() << " to " << w << std::endl;
    // }

    // if (this->rotation != 0){
    //     pixmap = pixmap.transformed(QTransform().rotate(-(this->rotation)));
    // }



    // img = pixmap.toImage();

    // if (this->contrast <100){
    //     std::cout << "contast = " << this->contrast << std::endl;
    //     for(int i=0;i<(img.height());i++){
    //         for(int j=0; j<(img.width()); j++){
    //             QColor p = img.pixelColor(j, i);
    //             if ((i== 1000) && (j==1000)) std::cout <<"whoola" << std::endl;
    //             int red = p.red();
    //             int green = p.green();
    //             int blue = p.blue();
    //             if (red>MR) MR=red;
    //             if (blue>MB) MB=blue;
    //             if (green>MG) MG=green;
    //             red = (int(red*100/contrast) > 255 ) ? 255 : int(red*100/contrast);
    //             green = (int(green*100/contrast) > 255) ? 255 : int(green*100/contrast);
    //             blue = (int(blue*100/contrast) > 255) ? 255 : int(blue*100/contrast);
    //             img.setPixelColor(j, i, QColor(red, green, blue, 255));
    //             // img.setPixelColor(j, i, QColor(10, 10, 10, 255));
    //             // if (alpha > M2) M2 = alpha;
    //         }
    //     }
    // }

    // std::cout << "Maximum pixel value = " << MR <<", "<< MG << ", "<<MB << std::endl;

    // pixmap2 = QPixmap::fromImage(img);
    // std::cout<< img.isGrayscale() << ", " << int(img.format())<<std::endl;
    // lb->setPixmap(pixmap2.scaled(pixmap2.width(), pixmap2.height(), Qt::KeepAspectRatio));
    // // lb->setText(QString("Hi bb "));
    // std::cout<<img.width() << ", "<<img.height()<< std::endl;
    // newsa->setWidget(lb);
    // newsa->setWidgetResizable(true);
    // newsa->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    // newsa->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    // // newsa->show();


    // QMdiSubWindow *subwin= this->ui->mdiArea->addSubWindow(newsa, Qt::Window);
    // // QMdiSubWindow *subwin = new QMdiSubWindow(this);
    // // subwin->setWidget(newsa);
    // subwin->setWindowTitle(item->text());
    // subwin->show();

    // // this->ui->mdiArea->tileSubWindows();


    // int p = this->ui->mdiArea->subWindowList().size();

    // this->ui->plainTextEdit->appendPlainText(QString::number(p));

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

void ImageViewer::updatePlotView()
{

    // int wp = this->ui->plotView->width();
    // int hp = this->ui->plotView->height();


    // this->plotBorder->setRect(5.0, 5.0, wp-5.0, hp-5.0);

    std::cout << "ImageViewer::updatePlotView() is called. "<< std::endl;
}



void ImageViewer::updatePanel(QMdiSubWindow* subwin)
{

    std::cout<<"Subwin Activated" << std::endl;
    this->updateHistogram();
    return;
}

void ImageViewer::updateHistogram()
{


    auto currentSubwin = this->ui->mdiArea->currentSubWindow();

    if(currentSubwin != nullptr) this->ui->plainTextEdit->appendPlainText(QString("update Histogram : ") + (currentSubwin->windowTitle()));

}
