#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "rect.h"

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

private:
    Ui::MainWindow *ui;
    std::vector<Rect*> towers[3];


protected:
    void paintEvent(QPaintEvent*) override;
private slots:
    void on_spinBox_valueChanged(int arg1);
    void on_pushButton_clicked();
};
#endif // MAINWINDOW_H
