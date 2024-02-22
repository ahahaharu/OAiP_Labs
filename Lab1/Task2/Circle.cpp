#include "Circle.h"

Circle::Circle()
{

}

void Circle::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    painter->setRenderHint(QPainter::Antialiasing, true);
    painter->drawEllipse(-r/2, -r/2, r, r);
}

float Circle::findArea()
{
    float s = this->getScale();
    return s*s*r*r*M_PI;
}

float Circle::findPerimeter()
{
    float s = this->getScale();
    return 2*M_PI*r*s;
}

void Circle::setR(int r) {
    this->r = r;
}

int Circle::getR() {
    return this->r;
}
