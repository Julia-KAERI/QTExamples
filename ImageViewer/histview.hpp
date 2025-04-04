#ifndef HISTVIEW_HPP
#define HISTVIEW_HPP

#include <QObject>
#include <QWidget>
#include <QGraphicsView>
#include <QPainterPath>
// #include <QGraphicsRectItem>
// #include <QGraphicsScene>
class HistView : public QGraphicsView
{
    Q_OBJECT
public:
    QPainterPath histpath;
    // QGraphicsScene *plotScene;
    // QGraphicsRectItem* plotBorder;
    explicit HistView(QWidget*);
    ~HistView();
    void plotHistogram(QVector<float>*);
protected:
    void resizeEvent(QResizeEvent*) override;
};

#endif // HISTVIEW_HPP
