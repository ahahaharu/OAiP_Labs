#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    wagon = new Wagon(this);
    wagon -> move(50, 100);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *)
{
    QPainter painter(this);

}

void MainWindow::on_pushButton_clicked()
{
    wagon -> moveRight();
}


void MainWindow::on_pushButton_2_clicked()
{
    wagon -> moveLeft();
}

