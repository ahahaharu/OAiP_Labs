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

void MainWindow::addError(QString errorMessage) {

    clearForm();
    QMessageBox::critical(nullptr, "Ошибка", errorMessage);

}

void MainWindow::clearForm() {
    ui->fioAdd_line->clear();
    ui->specAdd_line->clear();
    ui->groupAdd_line->clear();
    ui->oaipAdd_spinBox->setValue(0);
    ui->maAdd_spinBox->setValue(0);
    ui->agilaAdd_spinBox->setValue(0);
    ui->mlAdd_spinBox->setValue(0);
    ui->hisoryAdd_spinBox->setValue(0);
}

void MainWindow::on_AddButton_clicked()
{
    QString errorMessage = "";

    bool isErr = false;
    QString name = ui->fioAdd_line->text();
    QString spec = ui->specAdd_line->text();
    QString group = ui->groupAdd_line->text();
    int oaip_mark = ui->oaipAdd_spinBox->value();
    int ma_mark = ui->maAdd_spinBox->value();
    int agila_mark = ui->agilaAdd_spinBox->value();
    int ml_mark = ui->mlAdd_spinBox->value();
    int hist_mark = ui->hisoryAdd_spinBox->value();

    int row = ui->tableWidget->rowCount();
    ui->tableWidget->insertRow(row);

    students[row] = Student(name, spec, group, oaip_mark, ma_mark, agila_mark, ml_mark, hist_mark);

    if (students[row].isNameCorrect()) {
        QTableWidgetItem *col1Item = new QTableWidgetItem(name);
        ui->tableWidget->setItem(row,0,col1Item);
    } else {
        errorMessage += "Оишбка в написании ФИО!\nФИО должно содержать только буквы\nВаше написание: "+name+"\nПример правильного написания: Богданович Андрей Валерьевич";
        isErr = true;
    }
    if (students[row].isSpecCorrect()) {
        QTableWidgetItem *col2Item = new QTableWidgetItem(spec);
        ui->tableWidget->setItem(row,1,col2Item);
    } else {
        if (!errorMessage.isEmpty()) {
            errorMessage += "\n\n";
        }
        errorMessage += "Ошибка в написании наименования специальности!\nНаименование специальности должно содержать только буквы\nВаше написание: "+spec+"\nПример правильного написания: ИиТП";
        isErr = true;
    }
    if (students[row].isGroupCorrect()){
        QTableWidgetItem *col3Item = new QTableWidgetItem(group);
        ui->tableWidget->setItem(row,2,col3Item);
    } else {
        if (!errorMessage.isEmpty()) {
            errorMessage += "\n\n";
        }
        errorMessage += "Ошибка в написании номера группы!\nНомер группы состоит из 6 цифр\nВаше написание: "+group+"\nПример правильного написания: 353504";
        isErr = true;
    }
    if (!isErr) {
        QTableWidgetItem *col4Item = new QTableWidgetItem(QString::number(students[row].averageMark(), 'f', 1));
        ui->tableWidget->setItem(row,3,col4Item);
    }

    if (isErr) {
        ui->tableWidget->removeRow(row);
        addError(errorMessage);
    } else {
        ui->studentSelect_comboBox->addItem(students[row].getInitials());
    }

    clearForm();
}

