#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    deactivateEditBtns();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::deactivateEditBtns() {
    ui->fioEdit_line->setEnabled(false);
    ui->specEdit_line->setEnabled(false);
    ui->groupEdit_line->setEnabled(false);
    ui->oaipEdit_spinBox->setEnabled(false);
    ui->maEdit_spinBox->setEnabled(false);
    ui->agilaEdit_spinBox->setEnabled(false);
    ui->mlEdit_spinBOx->setEnabled(false);
    ui->historyEdit_spinBox->setEnabled(false);
    ui->edit_button->setEnabled(false);
    ui->delete_button->setEnabled(false);
}

void MainWindow::activateEditBtns() {
    ui->fioEdit_line->setEnabled(true);
    ui->specEdit_line->setEnabled(true);
    ui->groupEdit_line->setEnabled(true);
    ui->oaipEdit_spinBox->setEnabled(true);
    ui->maEdit_spinBox->setEnabled(true);
    ui->agilaEdit_spinBox->setEnabled(true);
    ui->mlEdit_spinBOx->setEnabled(true);
    ui->historyEdit_spinBox->setEnabled(true);
    ui->edit_button->setEnabled(true);
    ui->delete_button->setEnabled(true);
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

void MainWindow::clearEditForm() {
    ui->fioEdit_line->clear();
    ui->specEdit_line->clear();
    ui->groupEdit_line->clear();
    ui->oaipEdit_spinBox->setValue(0);
    ui->maEdit_spinBox->setValue(0);
    ui->agilaEdit_spinBox->setValue(0);
    ui->mlEdit_spinBOx->setValue(0);
    ui->historyEdit_spinBox->setValue(0);
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
        ui->studentSelect_comboBox->addItem(QString::number(row+1)+") "+students[row].getInitials());
    }

    clearForm();
}


void MainWindow::on_studentSelect_comboBox_currentIndexChanged(int i)
{
    curInd = i - 1;

    if (i == 0) {
        clearEditForm();
        deactivateEditBtns();
    } else {
        activateEditBtns();
        ui->fioEdit_line->setText(students[i-1].getName());
        ui->specEdit_line->setText(students[i-1].getSpec());
        ui->groupEdit_line->setText(students[i-1].getGroup());
        ui->oaipEdit_spinBox->setValue(students[i-1].getOaip());
        ui->maEdit_spinBox->setValue(students[i-1].getMa());
        ui->agilaEdit_spinBox->setValue(students[i-1].getAgila());
        ui->mlEdit_spinBOx->setValue(students[i-1].getMl());
        ui->historyEdit_spinBox->setValue(students[i-1].getHist());
    }
}


void MainWindow::on_edit_button_clicked()
{
    QString errorMessage = "";

    bool isErr = false;
    QString name = ui->fioEdit_line->text();
    QString spec = ui->specEdit_line->text();
    QString group = ui->groupEdit_line->text();
    int oaip_mark = ui->oaipEdit_spinBox->value();
    int ma_mark = ui->maEdit_spinBox->value();
    int agila_mark = ui->agilaEdit_spinBox->value();
    int ml_mark = ui->mlEdit_spinBOx->value();
    int hist_mark = ui->historyEdit_spinBox->value();

    students[curInd] = Student(name, spec, group, oaip_mark, ma_mark, agila_mark, ml_mark, hist_mark);

    if (students[curInd].isNameCorrect()) {
        QTableWidgetItem *col1Item = new QTableWidgetItem(name);
        ui->tableWidget->setItem(curInd,0,col1Item);
    } else {
        errorMessage += "Оишбка в написании ФИО!\nФИО должно содержать только буквы\nВаше написание: "+name+"\nПример правильного написания: Богданович Андрей Валерьевич";
        isErr = true;
    }
    if (students[curInd].isSpecCorrect()) {
        QTableWidgetItem *col2Item = new QTableWidgetItem(spec);
        ui->tableWidget->setItem(curInd,1,col2Item);
    } else {
        if (!errorMessage.isEmpty()) {
            errorMessage += "\n\n";
        }
        errorMessage += "Ошибка в написании наименования специальности!\nНаименование специальности должно содержать только буквы\nВаше написание: "+spec+"\nПример правильного написания: ИиТП";
        isErr = true;
    }
    if (students[curInd].isGroupCorrect()){
        QTableWidgetItem *col3Item = new QTableWidgetItem(group);
        ui->tableWidget->setItem(curInd,2,col3Item);
    } else {
        if (!errorMessage.isEmpty()) {
            errorMessage += "\n\n";
        }
        errorMessage += "Ошибка в написании номера группы!\nНомер группы состоит из 6 цифр\nВаше написание: "+group+"\nПример правильного написания: 353504";
        isErr = true;
    }
    if (!isErr) {
        QTableWidgetItem *col4Item = new QTableWidgetItem(QString::number(students[curInd].averageMark(), 'f', 1));
        ui->tableWidget->setItem(curInd,3,col4Item);
    }

    if (isErr) {
        ui->tableWidget->removeRow(curInd);
        addError(errorMessage);
    } else {
        ui->studentSelect_comboBox->setItemText(curInd+1, QString::number(curInd+1)+") "+students[curInd].getInitials());

    }

    ui->studentSelect_comboBox->setCurrentIndex(0);
}


void MainWindow::on_delete_button_clicked()
{
    int rowCount = ui->tableWidget->rowCount();
    ui->tableWidget->removeRow(curInd);

    for (int i = curInd; i < rowCount; i++) {
        students[i] = students[i+1];
    }

    ui->studentSelect_comboBox->removeItem(curInd+1);
    ui->studentSelect_comboBox->setCurrentIndex(0);

    for (int i = 1; i < rowCount; i++) {
        ui->studentSelect_comboBox->setItemText(i, QString::number(i)+") "+students[i-1].getInitials());
    }
}

