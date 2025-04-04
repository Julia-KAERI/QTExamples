#include "histview.hpp"
#include <iostream>
#include <QString>
#include <QGraphicsPathItem>
#include <QGraphicsScene>

HistView::HistView(QWidget *parent)
    : QGraphicsView(parent)
{
    // this->plotScene = new QGraphicsScene(this);
    // // this->setScene(this->plotScene);
    // // this->fitInView(this->sceneRect());
    // this->setScene(this->plotScene);
    // this->fitInView(this->sceneRect());
    // // hisgrogram plot's rectangle border line
    // int wp = this->width();
    // int hp = this->height();
    // this->plotBorder = this->scene()->addRect(QRect(5.0, 5.0, wp-5.0, hp-5.0), QPen(Qt::white), QBrush(1));

    // QGraphicsPathItem* ps;
    // ps = this->scene()->addPath(this->histpath,QPen(Qt::yellow), QBrush(1));
    // ps->setVisible(true);
    // ps->show();
}

HistView::~HistView()
{
    // delete this->plotScene;
}
void HistView::resizeEvent(QResizeEvent* event){
    this->fitInView(this->sceneRect());
    std::cout<< (this->items()).size() <<std::endl;
}

void HistView::plotHistogram(QVector<float>* hist){
    std::cout<< "hist" << hist->at(1)<< std::endl;
    // auto scene = this->scene();
    // this->plotBorder->rect().getRect(&rx, &ry, &rw, &rh);

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

}
