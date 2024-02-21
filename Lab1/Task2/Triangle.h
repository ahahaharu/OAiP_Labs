#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "Figure.h"

class Triangle : public Figure
{
public:
    Triangle();
    int a = 0;
    float findArea() override;
    float findPerimeter() override;
    void setA(int);
protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *) override;
};

#endif // TRIANGLE_H
