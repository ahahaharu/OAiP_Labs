#include "MovingRectangle.h"
// #include <QGraphicsItem>

MovingRectangle::MovingRectangle(QWidget *parent) : QWidget(parent)
{
    setFixedSize(400, 100);
}

void MovingRectangle::paintEvent(QPaintEvent *)
{
    QPainter painter(this);

    QRect rect(0, 0, 400, 100);

    painter.fillRect(rect, Qt::red);
}

void MovingRectangle::moveRight() {
    int a = x();
    animation = new QPropertyAnimation(this, "pos");
    animation -> setDuration(500);
    animation->setStartValue(pos());
    a += 25;
    if (a < 350) {
        animation->setEndValue(QPoint(a, y()));
        animation->start(QAbstractAnimation::DeleteWhenStopped);
    }
}

void MovingRectangle::moveLeft() {
    int a = x();
    animation = new QPropertyAnimation(this, "pos");
    animation -> setDuration(500);
    animation->setStartValue(pos());
    a -= 25;
    if (a > 50) {
        animation->setEndValue(QPoint(a, y()));
        animation->start(QAbstractAnimation::DeleteWhenStopped);
    }
}





