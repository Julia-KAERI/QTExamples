#include "imagewindow.hpp"
#include "ctimageviewer.hpp"
#include "ui_ctimageviewer.h"
#include <QMdiSubWindow>
#include <QString>
#include <QGraphicsPixmapItem>
#include <math.h>

CTImageViewer::CTImageViewer(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::CTImageViewer)
{
    ui->setupUi(this);

    // Image scale and contrast intialization
    this->ui->imageScaleSlider->setValue(100);
    this->ui->imageContrastSlider->setValue(100);

    this->ui->CB_rotation->setDisabled(true);
    this->ui->imageScaleSlider->setDisabled(true);
    this->ui->imageContrastSlider->setDisabled(true);
    this->ui->PB_applyToAll->setDisabled(true);

    this->histScene = new QGraphicsScene(this);
    int w = this->ui->graphicsView->width();
    int h = this->ui->graphicsView->height();
    std::cout << "width and height = of graphicsview " << w << ", " << h << std::endl;
    QPen col(Qt::white);
    QRect rect(5, 5, w-10, h-10); /*# Shouldn't this place the rectangle at 200 at x and y?*/
    histScene->addRect(rect, col);
    this->ui->graphicsView->setScene(histScene);

    this->histPath = QPainterPath();

    // this->ui->graphicsView->fitInView(this->ui->graphicsView->sceneRect());

    // QGraphicsScene *tscene = new QGraphicsScene(this);
    // this->ui->qimageview->setScene(tscene);

    connect(this->ui->actionOpen, SIGNAL(triggered(bool)), this, SLOT(openDir()));
    connect(this->ui->listWidget, SIGNAL(itemDoubleClicked(QListWidgetItem*)), this, SLOT(viewImage(QListWidgetItem*)));
    connect(this->ui->CB_rotation, SIGNAL(currentTextChanged(QString)), this, SLOT(rotateSubwindowImage(QString)));
    connect(this->ui->imageScaleSlider, SIGNAL(sliderReleased()), this, SLOT(transformSubwindowImage()));
    connect(this->ui->imageContrastSlider, SIGNAL(sliderReleased()), this, SLOT(transformSubwindowImage()));
    connect(this->ui->mdiArea, SIGNAL(subWindowActivated(QMdiSubWindow*)), this, SLOT(imageSelected(QMdiSubWindow*)));
    connect(this->ui->PB_applyToAll, SIGNAL(clicked()), this, SLOT(setGlobalParameters()));
    connect(this->ui->CB_yaxisScale, SIGNAL(currentIndexChanged(int)), this, SLOT(changeHistogramScale()));
}

CTImageViewer::~CTImageViewer()
{
    delete ui;
}

void CTImageViewer::openDir()
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

void CTImageViewer::viewImage(QListWidgetItem* lwitem){
    QList<QMdiSubWindow *> subwindowlist = this->ui->mdiArea->subWindowList();

    for(QMdiSubWindow *p: subwindowlist){
        if (p->windowTitle() == lwitem->text())
        {
            return ;
        }
    }

    QString itemPath = this->dataDir.absoluteFilePath(lwitem->text());

    ImageWindow* imv = new ImageWindow(this);
    imv->loadImageFile(itemPath, this->rotationAngle, this->scaleFactor, this->contrastFactor);
    QMdiSubWindow* subwin = this->ui->mdiArea->addSubWindow(imv);
    subwin->setWindowTitle(lwitem->text());
    subwin->show();

    ImageWindow *ss = static_cast<ImageWindow *>(subwin->widget());

    CTImageViewer::plotHist(ss->histdata);

    return;
}

void CTImageViewer::changeHistogramScale(){

    auto subwindow = this->ui->mdiArea->activeSubWindow();
    if (subwindow == nullptr) return;

    ImageWindow *ss = static_cast<ImageWindow *>(subwindow->widget());
    this->plotHist(ss->histdata);
}

void CTImageViewer::plotHist(QVector<float> hist){
    // float hmin = *std::min_element(hist.constBegin(), hist.constEnd());
    this->histPath.clear();
    int ymode = this->ui->CB_yaxisScale->currentIndex();
    if(ymode == 0){
        float hmax = *std::max_element(hist.constBegin(), hist.constEnd());
        int w = this->histScene->width();
        int h = this->histScene->height();
        std::cout << "width and height = of graphicsscene " << w << ", " << h << std::endl;
        qreal dx = float(w-10)/65536;
        qreal dy = float(h-10)/hmax;
        qreal hx, hy;
        int hl = hist.length();
        std::cout << "length of histogram =  " << hl << std::endl;
        for(int i = 0 ; i<hl; i++){
            hx = 5+i*dx;
            hy =  h-5 - (hist.at(i)*dy);
            if(i==0) histPath.moveTo(hx, hy);
            else {
                    histPath.lineTo(hx, hy);
            }
            if(i==(hl-1)){
                std::cout<<hx << ", " << hy << std::endl;
            }
        }
    }
    else{
        float hmax = *std::max_element(hist.constBegin(), hist.constEnd());
        int w = this->histScene->width();
        int h = this->histScene->height();
        std::cout << "width and height = of graphicsscene " << w << ", " << h << std::endl;
        qreal dx = float(w-10)/65536;
        qreal dy = float(h-10)/log(hmax);
        qreal hx, hy;
        int hl = hist.length();
        std::cout << "length of histogram =  " << hl << std::endl;
        for(int i = 0 ; i<hl; i++){
            hx = 5+i*dx;
            hy =  h-5 - log(hist.at(i)*dy+1.0);
            // hy =  5+(hist.at(i)*dy);
            if(i==0) histPath.moveTo(hx, hy);
            else {
                histPath.lineTo(hx, hy);
            }
            if(i==(hl-1)){
                std::cout<<hx << ", " << hy << std::endl;
            }
        }
    }

    this->histScene->addPath(histPath, QPen(Qt::yellow), QBrush(1));

}

void CTImageViewer::setListWidgetFont(QFont qf){
    this->ui->listWidget->setFont(qf);
}

void CTImageViewer::setPlainTextWidgetFont(QFont qf){
    this->ui->plainTextEdit->setFont(qf);
}

void CTImageViewer::imageSelected(QMdiSubWindow* subwindow){
    this->ui->CB_rotation->setDisabled(false);
    this->ui->imageScaleSlider->setDisabled(false);
    this->ui->imageContrastSlider->setDisabled(false);
    this->ui->PB_applyToAll->setDisabled(false);
    if (subwindow == nullptr) return;

    ImageWindow *iw = static_cast<ImageWindow *>(subwindow->widget());
    // iw->setParent(this);
    this->ui->CB_rotation->setCurrentText(QString::number(iw->rotationAngle));
    this->ui->imageScaleSlider->setValue(iw->scaleFactor);
    this->ui->imageContrastSlider->setValue(iw->contrastFactor);
}


void CTImageViewer::rotateSubwindowImage(QString sangle){
    int angle = sangle.toInt();
    auto subwindow = this->ui->mdiArea->activeSubWindow();
    if (subwindow == nullptr) return;

    ImageWindow *ss = static_cast<ImageWindow *>(subwindow->widget());
    // ss->setParent(this);
    ss->rotateImage(angle);
    this->ui->plainTextEdit->appendPlainText(ss->metaObject()->className());
    return;

}

void CTImageViewer::transformSubwindowImage() {
    int scale = this->ui->imageScaleSlider->value();
    int contrast = this->ui->imageContrastSlider->value();
    auto subwindow = this->ui->mdiArea->activeSubWindow();
    if (subwindow == nullptr) return;
    ImageWindow *ss = static_cast<ImageWindow *>(subwindow->widget());
    // ss->setParent(this);
    ss->transformImage(scale, contrast);

    // QGraphicsPixmapItem *item = new QGraphicsPixmapItem(QPixmap::fromImage(ig));
    // this->ui->graphicsView->scene() ->addItem(item);
}

void CTImageViewer::setGlobalParameters() {
    this->rotationAngle = this->ui->CB_rotation->currentText().toInt();
    this->scaleFactor = this->ui->imageScaleSlider->value();
    this->contrastFactor = this->ui->imageContrastSlider->value();

    std::cout << this->rotationAngle << ", " << this->scaleFactor << ", " << this->contrastFactor << std::endl;
}



