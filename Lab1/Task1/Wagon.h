#ifndef WAGON_H
#define WAGON_H

#include "MovingRectangle.h"

class Wagon : public MovingRectangle {
    Q_OBJECT
public:
    Wagon(QWidget* parent = nullptr);
protected:
    void paintEvent(QPaintEvent *) override;
};

#endif // WAGON_H
