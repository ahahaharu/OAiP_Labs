#include "squaredialog.h"
#include "ui_squaredialog.h"

SquareDialog::SquareDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::SquareDialog)
{
    ui->setupUi(this);
}

SquareDialog::~SquareDialog()
{
    delete ui;
}

void SquareDialog::on_buttonBox_accepted()
{
    QString a = ui->lineEdit->text();
    bool isOk;
    int b = a.toInt(&isOk);


    if (!isOk) {
        b = 0;
    }
    emit sendSquareSignals(b);
}

