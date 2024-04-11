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

void MainWindow::paintEvent(QPaintEvent*) {
    QPainter painter(this);
    QBrush brush(Qt::black);

    painter.drawRect(20, 20, 1880, 780);

    painter.setBrush(brush);
    painter.drawRect(310, 140, 40, 660);
    painter.drawRect(940, 140, 40, 660);
    painter.drawRect(1570, 140, 40, 660);

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

void MainWindow::on_spinBox_valueChanged(int n)
{
    // Удаляем старые диски
    for (int i = 0; i < towerSizes[0]; i++) {
        towers[0][i]->hide();
        towers[0][i]->deleteLater();
    }
    delete[] towers[0];
    towers[0] = new Rect*[n];
    towerSizes[0] = n;

    QCoreApplication::processEvents(); // Обрабатываем все ожидающие события удаления

    // Создаем новые диски
    for (int i = 0; i < n; i++) {
        Rect *rect = new Rect(n-i, this);
        rect->setPosition(310 - (n-i)*5, 800 - (i+1)*30);
        rect->show();
        towers[0][i] = rect;
    }
}

void hanoi(int n, Rect**& from, Rect**& to, Rect**& aux, int& sizeFrom, int& sizeTo, int& sizeAux, int x1, int x2, int x3) {
    if (n == 1) {
        Rect* rect = from[sizeFrom-1];
        Rect** newFrom = new Rect*[sizeFrom - 1]; // выделяем память для нового массива
        for(int i = 0; i < sizeFrom - 1; i++) {
            newFrom[i] = from[i]; // копируем старые элементы
        }
        delete[] from; // удаляем старый массив
        from = newFrom; // обновляем указатель
        sizeFrom--;
        moveRect(rect, x2, 800 - (sizeTo+1)*30); // перемещаем прямоугольник на новую позицию
        Rect** newTo = new Rect*[sizeTo + 1]; // выделяем память для нового элемента
        for(int i = 0; i < sizeTo; i++) {
            newTo[i] = to[i]; // копируем старые элементы
        }
        delete[] to; // удаляем старый массив
        newTo[sizeTo] = rect; // добавляем новый элемент
        to = newTo; // обновляем указатель
        sizeTo++;
        return;
    }
    hanoi(n - 1, from, aux, to, sizeFrom, sizeAux, sizeTo, x1, x3, x2);
    hanoi(1, from, to, aux, sizeFrom, sizeTo, sizeAux, x1, x2, x3);
    hanoi(n - 1, aux, to, from, sizeAux, sizeTo, sizeFrom, x3, x2, x1);
}



void MainWindow::on_pushButton_clicked()
{
    hanoi(towerSizes[0], towers[0], towers[2], towers[1], towerSizes[0], towerSizes[2], towerSizes[1], 310, 1570, 940);
}


