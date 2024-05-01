#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPainter>
#include <QPushButton>
#include <QTimer>
#include <QEventLoop>

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

public slots:
    void updateData(int newSize);

protected:
    void paintEvent(QPaintEvent*);

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

private:
    void heapSort();
    void heapify(int n, int i);
    void delay(int millisecondsToWait);

    int* m_data = nullptr;
    int m_size = 100;

    bool isSorting = false;

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
