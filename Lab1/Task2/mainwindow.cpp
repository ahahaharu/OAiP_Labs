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
        if (triangle->getA()) {
            scene->addItem(figure);
            updateValues();
            curF = 1;
        } else {
            figure = nullptr;
        }
    } else if (ui->comboBox->currentIndex() == 2) {
        scene->clear();
        figure = new Circle();
        Circle* circle = dynamic_cast<Circle*>(figure);
        connect(&circleD, &CircleDialog::sendCircleSignals, circle, &Circle::setR);
        connect(&circleD, &CircleDialog::sendCheckSignal, circle, &Circle::isCh);
        circleD.exec();
        if (circle->getR()) {
            scene->addItem(figure);
            updateValues();
            curF = 2;
        } else {
            figure = nullptr;
        }
    } else if (ui->comboBox->currentIndex() == 3) {
        scene->clear();
        figure = new Rhombus();
        Rhombus* rhombus = dynamic_cast<Rhombus*>(figure);
        connect(&rhombusD, &RhombusDialog::sendRhombusSignals, rhombus, &Rhombus::setAB);
        rhombusD.exec();
        if (rhombus->getA() && rhombus->getB()) {
            scene->addItem(figure);
            updateValues();
            curF = 3;
        } else {
            figure = nullptr;
        }
    } else if (ui->comboBox->currentIndex() == 4) {
        scene->clear();
        figure = new Square();
        Square* square = dynamic_cast<Square*>(figure);
        connect(&squareD, &SquareDialog::sendSquareSignals, square, &Square::setA);
        squareD.exec();
        if (square->getA()) {
            scene->addItem(figure);
            updateValues();
            curF = 4;
        } else {
            figure = nullptr;
        }
    } else if (ui->comboBox->currentIndex() == 5) {
        scene->clear();
        figure = new Rectangle();
        Rectangle* rectangle = dynamic_cast<Rectangle*>(figure);
        connect(&rectangleD, &RectangleDialog::sendRectangleSignals, rectangle, &Rectangle::setAB);
        rectangleD.exec();
        if (rectangle->getA() && rectangle->getB()) {
            scene->addItem(figure);
            updateValues();
            curF = 5;
        } else {
            figure = nullptr;
        }
    } else if (ui->comboBox->currentIndex() == 6) {
        scene->clear();
        figure = new Star5Pntd();
        Star5Pntd* star = dynamic_cast<Star5Pntd*>(figure);
        connect(&starD, &StarDialog::sendStarSignals, star, &Star5Pntd::setRs);
        connect(&starD, &StarDialog::sendRBtnsSignal, star, &Star5Pntd::setPoints);
        starD.exec();
        if (star->getPoints() == 6) {
            int r1, r2;
            r1 = star->getR1();
            r2 = star->getR2();
            figure = new Star6Pntd();
            Star6Pntd* star = dynamic_cast<Star6Pntd*>(figure);
            star->setRs(r1, r2);
        } else if (star->getPoints() == 8) {
            int r1, r2;
            r1 = star->getR1();
            r2 = star->getR2();
            figure = new Star8Pntd();
            Star8Pntd* star = dynamic_cast<Star8Pntd*>(figure);
            star->setRs(r1, r2);
        }
        if (star->getR1() && star->getR2()) {
            scene->addItem(figure);
            updateValues();
            curF = 6;
        } else {
            figure = nullptr;
        }
    } else if (ui->comboBox->currentIndex() == 7) {
        scene->clear();
        figure = new Hexagon();
        Hexagon* hex = dynamic_cast<Hexagon*>(figure);
        connect(&hexagonD, &HexagonDialog::sendHexagonSignals, hex, &Hexagon::setR);
        hexagonD.exec();
        if (hex->getR()) {
            scene->addItem(figure);
            updateValues();
            curF = 7;
        } else {
            figure = nullptr;
        }
    } else if (ui->comboBox->currentIndex() == 8) {
        scene->clear();
        figure = new Trapezoid();
        Trapezoid* trapezoid = dynamic_cast<Trapezoid*>(figure);
        connect(&trapezoidD, &TrapezoidDialog::sendTrapezoidSignals, trapezoid, &Trapezoid::setABH);
        trapezoidD.exec();
        if (trapezoid->getA() && trapezoid->getB() && trapezoid->getH()) {
            scene->addItem(figure);
            updateValues();
            curF = 8;
        } else {
            figure = nullptr;
        }
    }
}

void MainWindow::on_pushButton_moveUp_clicked()
{
    if (figure) {
        figure->moveUp();
        updateValues();
    }
}


void MainWindow::on_pushButton_moveRight_clicked()
{
    if (figure) {
        figure->moveRight();
        updateValues();
    }
}

void MainWindow::on_pushButton_moveDown_clicked()
{
    if (figure) {
        figure->moveDown();
        updateValues();
    }
}


void MainWindow::on_pushButton_moveLeft_clicked()
{
    if (figure) {
        figure->moveLeft();
        updateValues();
    }
}



void MainWindow::on_pushButton_2_clicked()
{
    if (figure) {
        figure->rotateLeft();
        updateValues();
    }
}


void MainWindow::on_pushButton_3_clicked()
{
    if (figure) {
        figure->rotateRight();
        updateValues();
    }
}


void MainWindow::on_pushButton_8_clicked()
{
    if (figure) {
        figure->upScale();
        updateValues();
    }
}


void MainWindow::on_pushButton_9_clicked()
{
    if (figure) {
        figure->downScale();
        updateValues();
    }
}



void MainWindow::on_spinBox_valueChanged(int arg1)
{
    if (figure) {
        figure->SBMoveX(arg1);
    }
}


void MainWindow::on_spinBox_2_valueChanged(int arg1)
{
    if (figure) {
        figure->SBMoveY(arg1);
    }
}


void MainWindow::on_pushButton_4_clicked()
{
    if (figure) {
        if (curF == 1) {
            Triangle* triangle = dynamic_cast<Triangle*>(figure);
            connect(&triangleD, &TriangleDialog::sendTriangleSignals, triangle, &Triangle::setA);
            triangleD.exec();

        } else if (curF == 2) {
            Circle* circle = dynamic_cast<Circle*>(figure);
            connect(&circleD, &CircleDialog::sendCircleSignals, circle, &Circle::setR);
            connect(&circleD, &CircleDialog::sendCheckSignal, circle, &Circle::isCh);
            circleD.exec();

        } else if (curF == 3) {
            Rhombus* rhombus = dynamic_cast<Rhombus*>(figure);
            connect(&rhombusD, &RhombusDialog::sendRhombusSignals, rhombus, &Rhombus::setAB);
            rhombusD.exec();
        } else if (curF == 4) {
            Square* square = dynamic_cast<Square*>(figure);
            connect(&squareD, &SquareDialog::sendSquareSignals, square, &Square::setA);
            squareD.exec();
        } else if (curF == 5) {
            Rectangle* rectangle = dynamic_cast<Rectangle*>(figure);
            connect(&rectangleD, &RectangleDialog::sendRectangleSignals, rectangle, &Rectangle::setAB);
            rectangleD.exec();
        } else if (curF == 6) {
            Star5Pntd* star = dynamic_cast<Star5Pntd*>(figure);
            connect(&starD, &StarDialog::sendStarSignals, star, &Star5Pntd::setRs);
            connect(&starD, &StarDialog::sendRBtnsSignal, star, &Star5Pntd::setPoints);
            starD.exec();
            if (star->getPoints() == 6) {
                int r1, r2;
                r1 = star->getR1();
                r2 = star->getR2();
                Star6Pntd* star = dynamic_cast<Star6Pntd*>(figure);
                star->setRs(r1, r2);
            } else if (star->getPoints() == 8) {
                int r1, r2;
                r1 = star->getR1();
                r2 = star->getR2();
                Star8Pntd* star = dynamic_cast<Star8Pntd*>(figure);
                star->setRs(r1, r2);
            }
        } else if (curF == 7) {
            Hexagon* hex = dynamic_cast<Hexagon*>(figure);
            connect(&hexagonD, &HexagonDialog::sendHexagonSignals, hex, &Hexagon::setR);
            hexagonD.exec();
        } else if (curF == 8) {
            Trapezoid* trapezoid = dynamic_cast<Trapezoid*>(figure);
            connect(&trapezoidD, &TrapezoidDialog::sendTrapezoidSignals, trapezoid, &Trapezoid::setABH);
            trapezoidD.exec();
        }
        scene->addItem(figure);
        updateValues();
    }
}


void MainWindow::on_pushButton_5_clicked()
{
    if (figure) {
        scene->clear();
        figure = nullptr;
        ui->spinBox->setValue(0);
        ui->spinBox_2->setValue(0);
        ui->areaLabel->setText("0");
        ui->perimeterLabel->setText("0");
    }
}


void MainWindow::on_pushButton_moveUp_pressed()
{
    connect(timer, SIGNAL(timeout()), this, SLOT(moveUpSlot()));
    timer->start(10);
}


void MainWindow::on_pushButton_moveUp_released()
{
    disconnect(timer, SIGNAL(timeout()), this, SLOT(moveUpSlot()));
    timer->stop();
}




void MainWindow::on_pushButton_moveRight_pressed()
{
    connect(timer, SIGNAL(timeout()), this, SLOT(moveRightSlot()));
    timer->start(10);
}


void MainWindow::on_pushButton_moveRight_released()
{
    disconnect(timer, SIGNAL(timeout()), this, SLOT(moveRightSlot()));
    timer->stop();
}


void MainWindow::on_pushButton_moveDown_pressed()
{
    connect(timer, SIGNAL(timeout()), this, SLOT(moveDownSlot()));
    timer->start(10);
}


void MainWindow::on_pushButton_moveDown_released()
{
    disconnect(timer, SIGNAL(timeout()), this, SLOT(moveDownSlot()));
    timer->stop();
}


void MainWindow::on_pushButton_moveLeft_pressed()
{
    connect(timer, SIGNAL(timeout()), this, SLOT(moveLeftSlot()));
    timer->start(10);
}


void MainWindow::on_pushButton_moveLeft_released()
{
    disconnect(timer, SIGNAL(timeout()), this, SLOT(moveLeftSlot()));
    timer->stop();
}


void MainWindow::on_pushButton_2_pressed()
{
    connect(timer, SIGNAL(timeout()), this, SLOT(rotateLeftSlot()));
    timer->start(10);
}


void MainWindow::on_pushButton_2_released()
{
    disconnect(timer, SIGNAL(timeout()), this, SLOT(rotateLeftSlot()));
    timer->stop();
}




void MainWindow::on_pushButton_3_pressed()
{
    connect(timer, SIGNAL(timeout()), this, SLOT(rotateRightSlot()));
    timer->start(10);
}


void MainWindow::on_pushButton_3_released()
{
    disconnect(timer, SIGNAL(timeout()), this, SLOT(rotateRightSlot()));
    timer->stop();
}


void MainWindow::on_pushButton_8_pressed()
{
    connect(timer, SIGNAL(timeout()), this, SLOT(upScaleSlot()));
    timer->start(10);
}


void MainWindow::on_pushButton_8_released()
{
    disconnect(timer, SIGNAL(timeout()), this, SLOT(upScaleSlot()));
    timer->stop();
}


void MainWindow::on_pushButton_9_pressed()
{
    connect(timer, SIGNAL(timeout()), this, SLOT(downScaleSlot()));
    timer->start(10);
}


void MainWindow::on_pushButton_9_released()
{
    disconnect(timer, SIGNAL(timeout()), this, SLOT(downScaleSlot()));
    timer->stop();
}

void MainWindow::moveUpSlot()
{
    if(figure) {
        figure->moveUp();
        updateValues();
    }
}

void MainWindow::moveDownSlot()
{
    if(figure) {
        figure->moveDown();
        updateValues();
    }
}

void MainWindow::moveRightSlot()
{
    figure->moveRight();
    updateValues();
}


void MainWindow::moveLeftSlot()
{
    if(figure) {
        figure->moveLeft();
        updateValues();
    }
}

void MainWindow::rotateRightSlot()
{
    figure->rotateRight();
    updateValues();
}

void MainWindow::rotateLeftSlot()
{
    if(figure) {
        figure->rotateLeft();
        updateValues();
    }
}


void MainWindow::upScaleSlot()
{
    if(figure) {
        figure->upScale();
        updateValues();
    }
}


void MainWindow::downScaleSlot()
{
    if(figure) {
        figure->downScale();
        updateValues();
    }
}

