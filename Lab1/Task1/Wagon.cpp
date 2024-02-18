#include "Wagon.h"

Wagon::Wagon(QWidget *parent) : MovingRectangle(parent)
{
    setFixedSize(400, 152);
}

void Wagon::paintEvent(QPaintEvent *)
{
    QPainter painter(this);

    QRect rect(0, 0, 400, 100);
    painter.fillRect(rect, Qt::red);

    painter.setBrush(Qt::black);
    painter.drawEllipse(QPoint(100, 100), 50, 50);
    painter.drawEllipse(QPoint(300, 100), 50, 50);
}
