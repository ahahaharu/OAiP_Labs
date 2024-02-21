#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "Figure.h"
#include <QTimer>
#include <QGraphicsScene>
#include <QGraphicsRectItem>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_moveUp_clicked();

    void on_pushButton_moveRight_clicked();

    void on_pushButton_moveDown_clicked();

    void on_pushButton_moveLeft_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_8_clicked();

    void on_pushButton_9_clicked();

private:
    Ui::MainWindow *ui;
    Figure *figure = nullptr;
    QTimer *timer;
    QGraphicsScene *scene;
protected:
    void paintEvent(QPaintEvent*);
};
#endif // MAINWINDOW_H
