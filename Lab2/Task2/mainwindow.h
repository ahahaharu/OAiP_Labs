#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include "student.h"

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
    void addError(QString);
    void clearForm();

    void on_AddButton_clicked();

private:
    Ui::MainWindow *ui;
    Student* students = new Student[100];

};
#endif // MAINWINDOW_H
