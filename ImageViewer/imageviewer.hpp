#ifndef IMAGEVIEWER_HPP
#define IMAGEVIEWER_HPP

#include <QMainWindow>
#include <QFileDialog>
QT_BEGIN_NAMESPACE
class QLabel;
namespace Ui {
class ImageViewer;

}
QT_END_NAMESPACE

class ImageViewer : public QMainWindow
{
    Q_OBJECT

public slots:
    void openFile();

public:
    ImageViewer(QWidget *parent = nullptr);
    void setLabelText(QString);
    void setLabelImage(QString fp = QString(""));
    ~ImageViewer();


    Ui::ImageViewer *ui;
private:
};
#endif // IMAGEVIEWER_HPP
