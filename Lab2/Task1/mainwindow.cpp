#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::on_addDat_button_clicked()
{
    QDate date = ui->dateEdit->date();
    int row = ui->tableWidget->rowCount();
    ui->tableWidget->insertRow(row);

    dates[row] = Date(date.day(), date.month(), date.year());

    QTableWidgetItem *col1Item = new QTableWidgetItem(dates[row].getDate());
    ui->tableWidget->setItem(row,0,col1Item);
    QTableWidgetItem *col2Item = new QTableWidgetItem(dates[row].NextDate().getDate());
    ui->tableWidget->setItem(row,1,col2Item);
    QTableWidgetItem *col3Item = new QTableWidgetItem("Следующий элемент не добавлен");
    ui->tableWidget->setItem(row,2,col3Item);

    if (row) {
        QTableWidgetItem *newDur = new QTableWidgetItem(QString::number(abs(dates[row].DateToDays() - dates[row-1].DateToDays())));
        ui->tableWidget->setItem(row-1, 2, newDur);
    }

    ui->Date_ComboBox->addItem(QString::number(row+1) + ") " + dates[row].getDate());
    QFile file("../dates.txt");

    if (!file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Append))
    {
        return;
    }
    QTextStream out(&file);
    out << dates[row].getDate()<<'\n';
}




void MainWindow::on_openFileButton_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), "", tr("Text Files (*.txt)"));

    if (fileName.isEmpty())
        return;

    QFile file(fileName);

    if (!file.open(QIODevice::ReadOnly)) {
        QMessageBox::information(this, tr("Unable to open file"), file.errorString());
        return;
    }
    int row = ui->tableWidget->rowCount();

    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine();
        ui->tableWidget->insertRow(row);
        dates[row] = StringToDate(line);
        QTableWidgetItem *col1Item = new QTableWidgetItem(dates[row].getDate());
        ui->tableWidget->setItem(row,0,col1Item);
        QTableWidgetItem *col2Item = new QTableWidgetItem(dates[row].NextDate().getDate());
        ui->tableWidget->setItem(row,1,col2Item);
        QTableWidgetItem *col3Item = new QTableWidgetItem("Следующий элемент не добавлен");
        ui->tableWidget->setItem(row,2,col3Item);

        if (row) {
            QTableWidgetItem *newDur = new QTableWidgetItem(QString::number(abs(dates[row].DateToDays() - dates[row-1].DateToDays())));
            ui->tableWidget->setItem(row-1, 2, newDur);
        }

        row++;
    }
}

