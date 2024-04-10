#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <stack>

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

void MainWindow::paintEvent(QPaintEvent*) {
    QPainter painter(this);
    QBrush brush(Qt::black);

    painter.drawRect(20, 20, 1880, 780);

    painter.setBrush(brush);
    painter.drawRect(310, 140, 40, 660);
    painter.drawRect(940, 140, 40, 660);
    painter.drawRect(1570, 140, 40, 660);

}

void MainWindow::on_spinBox_valueChanged(int n)
{
    // Удаляем старые диски
    for (Rect *rect : towers[0]) {
        rect->hide();
        rect->deleteLater();
    }
    towers[0].clear();

    QCoreApplication::processEvents(); // Обрабатываем все ожидающие события удаления

    // Создаем новые диски
    for (int i = n-1; i >= 0; i--) {
        Rect *rect = new Rect(i+1, this);
        rect->setPosition(310 - (i+1)*5, 800 - (n-i)*30);
        rect->show();
        towers[0].push_back(rect);
    }
}


void moveRect(Rect* rect, int x, int y) {
    int halfWidth = 20; // половина ширины столба

    // Поднимаем прямоугольник вверх
    QPropertyAnimation *animation1 = new QPropertyAnimation(rect, "geometry");
    animation1->setDuration(500); // продолжительность анимации в миллисекундах
    animation1->setStartValue(rect->geometry()); // начальное положение - текущее положение прямоугольника
    animation1->setEndValue(QRect(rect->x(), 40, rect->width(), rect->height())); // конечное положение - прямоугольник поднят вверх
    animation1->start(QAbstractAnimation::DeleteWhenStopped); // начинаем анимацию и удаляем ее, когда она закончится

    QEventLoop loop;
    QObject::connect(animation1, SIGNAL(finished()), &loop, SLOT(quit()));
    loop.exec();

    // Перемещаем прямоугольник влево или вправо
    QPropertyAnimation *animation2 = new QPropertyAnimation(rect, "geometry");
    animation2->setDuration(500); // продолжительность анимации в миллисекундах
    animation2->setStartValue(QRect(rect->x(), 40, rect->width(), rect->height())); // начальное положение - прямоугольник находится наверху
    animation2->setEndValue(QRect(x - rect->width()/2 + halfWidth, 40, rect->width(), rect->height())); // конечное положение - прямоугольник перемещен влево или вправо
    animation2->start(QAbstractAnimation::DeleteWhenStopped); // начинаем анимацию и удаляем ее, когда она закончится

    QObject::connect(animation2, SIGNAL(finished()), &loop, SLOT(quit()));
    loop.exec();

    // Опускаем прямоугольник вниз
    QPropertyAnimation *animation3 = new QPropertyAnimation(rect, "geometry");
    animation3->setDuration(500); // продолжительность анимации в миллисекундах
    animation3->setStartValue(QRect(x - rect->width()/2 + halfWidth, 40, rect->width(), rect->height())); // начальное положение - прямоугольник находится вверху
    animation3->setEndValue(QRect(x - rect->width()/2 + halfWidth, y, rect->width(), rect->height())); // конечное положение - новое положение прямоугольника
    animation3->start(QAbstractAnimation::DeleteWhenStopped); // начинаем анимацию и удаляем ее, когда она закончится

    QObject::connect(animation3, SIGNAL(finished()), &loop, SLOT(quit()));
    loop.exec();
}





void hanoi(int n, std::vector<Rect*>& from, std::vector<Rect*>& to, std::vector<Rect*>& aux, int x1, int x2, int x3) {
    if (n == 1) {
        Rect* rect = from.back();
        from.pop_back();
        moveRect(rect, x2, 800 - (to.size()+1)*30); // перемещаем прямоугольник на новую позицию
        to.push_back(rect);
        return;
    }
    hanoi(n - 1, from, aux, to, x1, x3, x2);
    hanoi(1, from, to, aux, x1, x2, x3);
    hanoi(n - 1, aux, to, from, x3, x2, x1);
}

void MainWindow::on_pushButton_clicked()
{
    // Вызываем функцию hanoi
    hanoi(ui->spinBox->value(), towers[0], towers[2], towers[1], 310, 1570, 940);
}

