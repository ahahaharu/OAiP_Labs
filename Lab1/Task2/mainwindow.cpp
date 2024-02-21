#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    timer = new QTimer();
    scene = new QGraphicsScene();
    ui->graphicsView->setScene(scene);


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *)
{
    QPainter *p = new QPainter(this);
    p->setRenderHint(QPainter::Antialiasing, true);
    p->setPen(Qt::black);
    p->end();
}

void MainWindow::on_pushButton_clicked()
{
    scene->clear();
    figure = new Figure;
    scene->addItem(figure);

}


void MainWindow::on_pushButton_moveUp_clicked()
{
    figure->moveUp();
}


void MainWindow::on_pushButton_moveRight_clicked()
{
    figure->moveRight();
}

void MainWindow::on_pushButton_moveDown_clicked()
{
    figure->moveDown();
}


void MainWindow::on_pushButton_moveLeft_clicked()
{
    figure->moveLeft();
}



void MainWindow::on_pushButton_2_clicked()
{
    figure->rotateLeft();
}


void MainWindow::on_pushButton_3_clicked()
{
    figure->rotateRight();
}


void MainWindow::on_pushButton_8_clicked()
{
    figure->upScale();
}


void MainWindow::on_pushButton_9_clicked()
{
    figure->downScale();
}


