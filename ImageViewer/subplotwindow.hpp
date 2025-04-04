#ifndef SUBPLOTWINDOW_HPP
#define SUBPLOTWINDOW_HPP

#include <QWidget>
#include <QList>
#include <QString>
#include <QPixmap>
#include <opencv2/opencv.hpp>
namespace Ui {
class SubplotWindow;
}

class SubplotWindow : public QWidget
{
    Q_OBJECT

public:
    QVector<float> histdata;
    QString filePath;
    QPixmap imagePixmap;

    void load(QString);
    void transform(int, int, int);
    void setPixmap(QPixmap);


    explicit SubplotWindow(QWidget *parent = nullptr);

    ~SubplotWindow();

private:
    Ui::SubplotWindow *ui;
};

#endif // SUBPLOTWINDOW_HPP
