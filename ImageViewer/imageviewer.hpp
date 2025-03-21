#ifndef IMAGEVIEWER_HPP
#define IMAGEVIEWER_HPP

#include <QMainWindow>
#include <QFileDialog>
#include <QLabel>
#include <QPixmap>
#include <QFont>
#include <QListWidgetItem>
#include <QMdiArea>
#include <QMdiSubWindow>
#include "dialog.hpp"

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
    void openDir();
    void plotItem(QListWidgetItem*);
    void configScale();

public:
    QDir dataDir;
    Dialog *configDlg;
    int rotation=0;
    int scale=100;
    int contrast=100;
    ImageViewer(QWidget *parent = nullptr);
    void setLabelText(QString);
    void setLabelImage(QString fp = QString(""));
    ~ImageViewer();


    Ui::ImageViewer *ui;
private:
};

#endif // IMAGEVIEWER_HPP

