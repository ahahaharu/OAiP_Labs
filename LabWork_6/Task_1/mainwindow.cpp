#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    Sportsman sportsman1{"Andrey", 18, 1.82, 'm', false, {1, 3, 8}};

    ui->struct1->setText(ui->struct1->text()+print(sportsman1));

    Sportsman sportsman2;
    strcpy(sportsman2.name, "Daria");
    sportsman2.age = 27;
    sportsman2.height = 1.64;
    sportsman2.gender = 'f';
    sportsman2.isActive = true;
    sportsman2.medals[0] = 0;
    sportsman2.medals[1] = 2;
    sportsman2.medals[2] = 1;

    ui->struct2->setText(ui->struct2->text()+print(sportsman2));

    Sportsman sportsman3;
    Sportsman* pointer = &sportsman3;

    strcpy(pointer->name, "Misha");
    pointer->age = 19;
    pointer->height = 1.95;
    pointer->gender = 'm';
    pointer->isActive = true;
    pointer->medals[0] = 10;
    pointer->medals[1] = 32;
    pointer->medals[2] = 45;

    ui->struct3->setText(ui->struct3->text()+print(*pointer));

    Sportsman sportsman4;

    strcpy((&sportsman4)->name, "Misha");
    (&sportsman4)->age = 19;
    (&sportsman4)->height = 1.95;
    (&sportsman4)->gender = 'm';
    (&sportsman4)->isActive = true;
    (&sportsman4)->medals[0] = 10;
    (&sportsman4)->medals[1] = 32;
    (&sportsman4)->medals[2] = 45;

    ui->struct4->setText(ui->struct4->text()+print(*(&sportsman4)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

QString MainWindow::print(Sportsman sportsman) {
    return QString(sportsman.name) + " | " + QString::number(sportsman.age) + " | " +
           QString::number(sportsman.height) + " | " +
           sportsman.gender + " | " +
           (sportsman.isActive ? "true" : "false") + " | {" +
           QString::number(sportsman.medals[0]) + ", " + QString::number(sportsman.medals[1]) + ", " + QString::number(sportsman.medals[2]) + '}';
}

void MainWindow::on_addButton_clicked()
{
    QString errorString = "";
    bool isError = false;
    Sportsman sportsman;

    if (ui->nameInput->text().isEmpty()) {
        errorString += "Имя не может быть пустым\n";
        isError = true;
    } else {
        QString name = ui->nameInput->text();
        strncpy(sportsman.name, name.toStdString().c_str(), 19);
    }

    sportsman.age = ui->ageInput->value();
    sportsman.height = ui->heightInput->value();

    QString gender = ui->genderInput->text();
    if (!(gender == 'm' || gender == 'f')) {
        errorString += "Пол может быть только m (male) или f (female)\n";
        isError = true;
    } else {
        sportsman.gender = gender.at(0).toLatin1();
    }

    if (ui->isActiveYES) {
        sportsman.isActive = true;
    } else {
        sportsman.isActive = false;
    }

    sportsman.medals[0] = ui->goldInput->value();
    sportsman.medals[1] = ui->silverInput->value();
    sportsman.medals[2] = ui->bronzeInput->value();

    if (isError) {
        QMessageBox::critical(0, "Ошибка добавления", errorString);
    } else {
        ui->struct5->setText("Структура 5: "+print(sportsman));
    }
}

