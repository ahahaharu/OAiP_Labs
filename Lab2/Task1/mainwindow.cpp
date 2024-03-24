#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->selectedDate_DateEdit->hide();
    deactivateBtns();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::deactivateBtns() {
    ui->changeDate_button->setEnabled(false);
    ui->nextDay_button->setEnabled(false);
    ui->prevDay_button->setEnabled(false);
    ui->isLeap_button->setEnabled(false);
    ui->WeekNum_button->setEnabled(false);
    ui->Duration_button->setEnabled(false);
}

void MainWindow::activateBtns(){
    ui->changeDate_button->setEnabled(true);
    ui->nextDay_button->setEnabled(true);
    ui->prevDay_button->setEnabled(true);
    ui->isLeap_button->setEnabled(true);
    ui->WeekNum_button->setEnabled(true);
    ui->Duration_button->setEnabled(true);
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

        ui->Date_ComboBox->addItem(QString::number(row+1) + ") " + dates[row].getDate());

        row++;
    }
}


void MainWindow::on_SelectDate_button_clicked()
{
    int ind = ui->Date_ComboBox->currentIndex();
    if (ind == 0) {
        QMessageBox::critical(nullptr, "Ошибка", "Дата не выбрана!\nВыберите дату в списке выше");
    } else {
        QDate date = QDate::fromString(dates[ind-1].getDate(), "dd.MM.yyyy");

        ui->selectedDate_label->hide();
        ui->selectedDate_DateEdit->setDate(date);
        ui->selectedDate_DateEdit->show();
        curDateInd = ind - 1;
    }

    activateBtns();
}


void MainWindow::on_changeDate_button_clicked()
{
    QDate date = ui->selectedDate_DateEdit->date();
    dates[curDateInd] = Date(date.day(), date.month(), date.year());

    QTableWidgetItem *col1Item = new QTableWidgetItem(dates[curDateInd].getDate());
    ui->tableWidget->setItem(curDateInd,0,col1Item);
    QTableWidgetItem *col2Item = new QTableWidgetItem(dates[curDateInd].NextDate().getDate());
    ui->tableWidget->setItem(curDateInd,1,col2Item);

    if(curDateInd == ui->tableWidget->rowCount() - 1) {
        QTableWidgetItem *col3Item = new QTableWidgetItem("Следующий элемент не добавлен");
        ui->tableWidget->setItem(curDateInd,2,col3Item);
    } else {
        QTableWidgetItem *newDur = new QTableWidgetItem(QString::number(abs(dates[curDateInd].DateToDays() - dates[curDateInd+1].DateToDays())));
        ui->tableWidget->setItem(curDateInd, 2, newDur);
    }

    if (curDateInd) {
        QTableWidgetItem *newDur = new QTableWidgetItem(QString::number(abs(dates[curDateInd].DateToDays() - dates[curDateInd-1].DateToDays())));
        ui->tableWidget->setItem(curDateInd-1, 2, newDur);
    }
}


void MainWindow::on_nextDay_button_clicked()
{
    QMessageBox msgBox;
    msgBox.setText("Следующий день: "+dates[curDateInd].NextDate().getDate());
    msgBox.exec();
}


void MainWindow::on_prevDay_button_clicked()
{
    QMessageBox msgBox;
    msgBox.setText("Предыдущий день: "+dates[curDateInd].PreviousDate().getDate());
    msgBox.exec();
}


void MainWindow::on_isLeap_button_clicked()
{
    QMessageBox msgBox;
    if (dates[curDateInd].IsLeap()) {
        msgBox.setText("Этот год високосный");
    } else {
        msgBox.setText("Этот год не високосный");
    }
    msgBox.exec();
}


void MainWindow::on_WeekNum_button_clicked()
{
    QMessageBox msgBox;
    msgBox.setText("Номер недели в году: "+QString::number(dates[curDateInd].WeekNumber()));
    msgBox.exec();
}


void MainWindow::on_Duration_button_clicked()
{
    QMessageBox msgBox;
    msgBox.setText("Количество дней между текущей и данной датой: "+QString::number(dates[curDateInd].Duration(dates[curDateInd])));
    msgBox.exec();
}

