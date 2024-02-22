#ifndef CIRCLE_H
#define CIRCLE_H

#include "Figure.h"

class Circle : public Figure
{
public:
    Circle();
    int r = 0;
    float findArea() override;
    float findPerimeter() override;
    void setR(int);
    int getR();
protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *) override;
};

#endif // CIRCLE_H
