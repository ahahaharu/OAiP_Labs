#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    updateData(m_size);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::updateData(int newSize) {
    if(m_data != nullptr)
    {
        delete[] m_data;
    }
    m_size = newSize;
    m_data = new int[m_size];
    for (int i = 0; i < m_size; ++i) {
        m_data[i] = rand() % 700;
    }
}

void MainWindow::paintEvent(QPaintEvent*) {
    qDebug() << m_data[0];
    QPainter painter(this);

    QBrush brush(Qt::black);

    painter.drawRect(20, 20, 1200, 700);
    painter.setBrush(Qt::blue);

    if (m_size != 0) {
        int w = 1200 / m_size;
        for(int i = 0; i < m_size; ++i) {
            painter.drawRect(20 + i * w, 720, w, -m_data[i]);
        }
    }
}

void MainWindow::heapSort()
{
    // Построение кучи (перегруппировка массива)
    for (int i = m_size / 2 - 1; i >= 0 && isSorting; i--)
        heapify(m_size, i);

    // Один за другим извлекаем элемент из кучи
    for (int i = m_size - 1; i >= 0 && isSorting; i--) {
        // Перемещаем текущий корень в конец
        std::swap(m_data[0], m_data[i]);

        // вызываем процедуру heapify на уменьшенной куче
        heapify(i, 0);
        delay(50);  // Задержка в 50 миллисекунд
        update();
    }
}

void MainWindow::heapify(int n, int i)
{
    int largest = i; // Инициализируем наибольший элемент как корень
    int left = 2 * i + 1; // левый = 2*i + 1
    int right = 2 * i + 2; // правый = 2*i + 2

    // Если левый дочерний элемент больше корня
    if (left < n && m_data[left] > m_data[largest])
        largest = left;

    // Если правый дочерний элемент больше, чем самый большой элемент на данный момент
    if (right < n && m_data[right] > m_data[largest])
        largest = right;

    // Если самый большой элемент не корень
    if (largest != i) {
        std::swap(m_data[i], m_data[largest]);

        // Рекурсивно преобразуем в двоичную кучу затронутое поддерево
        heapify(n, largest);
    }
}

void MainWindow::delay(int millisecondsToWait)
{
    QEventLoop loop;
    QTimer::singleShot(millisecondsToWait, &loop, &QEventLoop::quit);
    loop.exec();
}

void MainWindow::on_pushButton_clicked() // запустить сортировку
{
    isSorting = true;
    update();
    heapSort();
}


void MainWindow::on_pushButton_2_clicked() // остановить сортировку
{
    isSorting = false;
}


void MainWindow::on_pushButton_3_clicked() // задать случайные значения
{
    isSorting = false;
    int size = ui->spinBox->value();
    updateData(size);
    update();
}

