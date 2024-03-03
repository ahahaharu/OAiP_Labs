#include "MovingRectangle.h"
#include <QMessageBox>

MovingRectangle::MovingRectangle(QWidget *parent) : QWidget(parent)
{
    setFixedSize(400, 100);
}

void MovingRectangle::paintEvent(QPaintEvent *)
{

}

void MovingRectangle::moveRight() {
    int a = x();
    a += 5;
    if (a < 801) {
        move(a, y());
    } else {
        QMessageBox::critical(nullptr, "Ошибка", "Вагон вышел за пределы окна!\nВагон будет возвращён в изначальное положение");
        move(50, y());
    }
}

void MovingRectangle::moveLeft() {
    int a = x();
    a -= 5;
    if (a > -400) {
        move(a, y());
    } else {
        QMessageBox::critical(nullptr, "Ошибка", "Вагон вышел за пределы окна!\nВагон будет возвращён в изначальное положение");
        move(50, y());
    }

}





