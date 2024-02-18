#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "MovingRectangle.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    rect = new MovingRectangle(this);
    rect -> move(50, 100);
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
    rect -> moveRight();
}


void MainWindow::on_pushButton_2_clicked()
{
    rect -> moveLeft();
}

