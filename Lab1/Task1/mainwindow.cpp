#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTimer>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    wagon = new Wagon(this);
    wagon -> move(50, 100);

    timerRight = new QTimer(this);
    timerLeft = new QTimer(this);

    connect(timerRight, &QTimer::timeout, wagon, &Wagon::moveRight);
    connect(timerLeft, &QTimer::timeout, wagon, &Wagon::moveLeft);
    connect(ui->pushButton, &QPushButton::pressed, this, &MainWindow::on_pushButton_pressed);
    connect(ui->pushButton, &QPushButton::released, this, &MainWindow::on_pushButton_released);
    connect(ui->pushButton_2, &QPushButton::pressed, this, &MainWindow::on_pushButton_2_pressed);
    connect(ui->pushButton_2, &QPushButton::released, this, &MainWindow::on_pushButton_2_released);
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


void MainWindow::on_pushButton_pressed()
{
    timerRight -> start(50);
}


void MainWindow::on_pushButton_released()
{
    timerRight ->stop();
}


void MainWindow::on_pushButton_2_pressed()
{
    timerLeft -> start(50);
}


void MainWindow::on_pushButton_2_released()
{
    timerLeft ->stop();
}

