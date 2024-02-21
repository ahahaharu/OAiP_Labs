#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "triangledialog.h"
#include <QDebug>


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

void MainWindow::updateValues()
{

    ui->spinBox->setValue(figure->getCenter().x());
    ui->spinBox_2->setValue(figure->getCenter().y());
    ui->areaLabel->setText(QString::number(figure->findArea(), 'f', 2));
    ui->perimeterLabel->setText(QString::number(figure->findPerimeter(), 'f', 2));
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
    if (ui->comboBox->currentIndex() == 0) {

    } else if (ui->comboBox->currentIndex() == 1){
        scene->clear();
        figure = new Triangle();
        Triangle* triangle = dynamic_cast<Triangle*>(figure);
        connect(&triangleD, &TriangleDialog::sendTriangleSignals, triangle, &Triangle::setA);
        triangleD.exec();
        scene->addItem(figure);
        updateValues();

    }
}

void MainWindow::on_pushButton_moveUp_clicked()
{
    figure->moveUp();
    updateValues();
}


void MainWindow::on_pushButton_moveRight_clicked()
{
    figure->moveRight();
    updateValues();
}

void MainWindow::on_pushButton_moveDown_clicked()
{
    figure->moveDown();
    updateValues();
}


void MainWindow::on_pushButton_moveLeft_clicked()
{
    figure->moveLeft();
    updateValues();
}



void MainWindow::on_pushButton_2_clicked()
{
    figure->rotateLeft();
    updateValues();
}


void MainWindow::on_pushButton_3_clicked()
{
    figure->rotateRight();
    updateValues();
}


void MainWindow::on_pushButton_8_clicked()
{
    figure->upScale();
    updateValues();
}


void MainWindow::on_pushButton_9_clicked()
{
    figure->downScale();
    updateValues();
}



void MainWindow::on_spinBox_valueChanged(int arg1)
{
    figure->SBMoveX(arg1);
}


void MainWindow::on_spinBox_2_valueChanged(int arg1)
{
    figure->SBMoveY(arg1);
}

