#include "dialog.hpp"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
{
    ui->setupUi(this);
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::setValue(int angle, int scale, int contrast)
{
    this->ui->comboBox->setCurrentText(QString::number(angle));
    this->ui->scaleSlider->setValue(scale);
    this->ui->contrastSlider->setValue(contrast);
}

QList<int> Dialog::getValue()
{
    int angle = (this->ui->comboBox->currentText()).toInt();
    int scale = this->ui->scaleSlider->value();
    int contrast = this->ui->contrastSlider->value();

    return QList<int>{angle, scale, contrast};
}
