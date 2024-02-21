#include "Figure.h"


void Figure::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{

}

Figure::Figure()
{

}

QRectF Figure::boundingRect() const
{
    return QRectF(-500,-500,1000,1000);
}


QPoint Figure::getCenter()
{
    return QPoint(this->x(), this->y());
}

void Figure::moveRight() {
    int a = x();
    animation = new QPropertyAnimation(this, "pos");
    animation -> setDuration(500);
    animation->setStartValue(pos());
    a += 50;
    animation->setEndValue(QPoint(a, y()));
    animation->start(QAbstractAnimation::DeleteWhenStopped);
}

void Figure::moveLeft() {
    int a = x();
    animation = new QPropertyAnimation(this, "pos");
    animation -> setDuration(500);
    animation->setStartValue(pos());
    a -= 50;
    animation->setEndValue(QPoint(a, y()));
    animation->start(QAbstractAnimation::DeleteWhenStopped);
}

void Figure::moveUp()
{
    int a = y();
    animation = new QPropertyAnimation(this, "pos");
    animation -> setDuration(500);
    animation->setStartValue(pos());
    a -= 50;
    animation->setEndValue(QPoint(x(), a));
    animation->start(QAbstractAnimation::DeleteWhenStopped);
}

void Figure::moveDown()
{
    int a = y();
    animation = new QPropertyAnimation(this, "pos");
    animation -> setDuration(500);
    animation->setStartValue(pos());
    a += 50;
    animation->setEndValue(QPoint(x(), a));
    animation->start(QAbstractAnimation::DeleteWhenStopped);
}

void Figure::rotateRight()
{
    animation = new QPropertyAnimation(this, "rotation");
    animation->setDuration(500);
    animation->setStartValue(rotation());
    animation->setEndValue(rotation()+10);
    animation->start(QAbstractAnimation::DeleteWhenStopped);
}


void Figure::rotateLeft()
{
    animation = new QPropertyAnimation(this, "rotation");
    animation->setDuration(500);
    animation->setStartValue(rotation());
    animation->setEndValue(rotation()-10);
    animation->start(QAbstractAnimation::DeleteWhenStopped);
}

void Figure::upScale()
{
    animation = new QPropertyAnimation(this, "scale");
    animation->setDuration(500);
    animation->setStartValue(scale);
    animation->setEndValue(scale*1.1);
    animation->start();

    scale = scale*1.1;

}

void Figure::downScale()
{
    animation = new QPropertyAnimation(this, "scale");
    animation->setDuration(500);
    animation->setStartValue(scale);
    animation->setEndValue(scale/1.1);
    animation->start();

    scale = scale/1.1;

}

float Figure::getScale() {
    return scale;
}

float Figure::findArea()
{
    return 0;
}

float Figure::findPerimeter()
{
    return 0;
}

void Figure::SBMoveX(int x)
{
    this->setPos(x, y());
}

void Figure::SBMoveY(int y)
{
    this->setPos(x(), y);
}
