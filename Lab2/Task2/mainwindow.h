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
    void clearEditForm();
    void activateEditBtns();
    void deactivateEditBtns();

    void on_AddButton_clicked();

    void on_studentSelect_comboBox_currentIndexChanged(int index);

    void on_edit_button_clicked();

    void on_delete_button_clicked();

private:
    Ui::MainWindow *ui;
    Student* students = new Student[100];
    int curInd = 0;

};
#endif // MAINWINDOW_H
