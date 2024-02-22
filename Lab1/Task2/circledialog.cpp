#include "circledialog.h"
#include "ui_circledialog.h"

CircleDialog::CircleDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::CircleDialog)
{
    ui->setupUi(this);
}

CircleDialog::~CircleDialog()
{
    delete ui;
}

void CircleDialog::on_buttonBox_accepted()
{
    QString a = ui->lineEdit->text();
    bool isOk;
    int b = a.toInt(&isOk);


    if (!isOk) {
        b = 0;
    }
    emit sendCircleSignals(b);
}

