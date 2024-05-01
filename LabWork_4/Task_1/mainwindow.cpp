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
    tempData = new int[m_size];
    for (int i = 0; i < m_size; ++i) {
        m_data[i] = rand() % 700;
        tempData[i] = m_data[i];
    }


}

void MainWindow::paintEvent(QPaintEvent*) {
    QPainter painter(this);

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

void MainWindow::heapSortTimer()
{
    // Построение кучи (перегруппировка массива)
    for (int i = m_size / 2 - 1; i >= 0 && isSorting; i--)
        heapifyTimer(m_size, i);

    // Один за другим извлекаем элемент из кучи
    for (int i = m_size - 1; i >= 0 && isSorting; i--) {
        // Перемещаем текущий корень в конец
        std::swap(tempData[0], tempData[i]);

        // вызываем процедуру heapify на уменьшенной куче
        heapifyTimer(i, 0);
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

void MainWindow::heapifyTimer(int n, int i)
{
    int largest = i; // Инициализируем наибольший элемент как корень
    int left = 2 * i + 1; // левый = 2*i + 1
    int right = 2 * i + 2; // правый = 2*i + 2

    // Если левый дочерний элемент больше корня
    if (left < n && tempData[left] > tempData[largest])
        largest = left;

    // Если правый дочерний элемент больше, чем самый большой элемент на данный момент
    if (right < n && tempData[right] > tempData[largest])
        largest = right;

    // Если самый большой элемент не корень
    if (largest != i) {
        std::swap(tempData[i], tempData[largest]);

        // Рекурсивно преобразуем в двоичную кучу затронутое поддерево
        heapify(n, largest);
    }
}

void MainWindow::quickSort(int low, int high)
{
    if (low < high && isSorting)
    {
        /* pi - индекс опорного элемента */
        int pi = partition(low, high);

        // Рекурсивно сортируем элементы до и после опорного
        quickSort(low, pi - 1);
        quickSort(pi + 1, high);
    }
}

void MainWindow::quickSortTimer(int low, int high)
{
    if (low < high && isSorting)
    {
        /* pi - индекс опорного элемента */
        int pi = partitionTimer(low, high);

        // Рекурсивно сортируем элементы до и после опорного
        quickSortTimer(low, pi - 1);
        quickSortTimer(pi + 1, high);
    }
}

int MainWindow::partition(int low, int high)
{
    // Опорный элемент (принимаем за опорный последний элемент)
    int pivot = m_data[high];
    int i = (low - 1); // Индекс меньшего элемента

    for (int j = low; j <= high - 1 && isSorting; j++)
    {
        // Если текущий элемент меньше или равен опорному
        if (m_data[j] <= pivot)
        {
            i++; // увеличиваем индекс меньшего элемента
            std::swap(m_data[i], m_data[j]);
            delay(50);  // Задержка в 50 миллисекунд
            update();
        }
    }
    std::swap(m_data[i + 1], m_data[high]);
    delay(50);  // Задержка в 50 миллисекунд
    update();
    return (i + 1);
}

int MainWindow::partitionTimer(int low, int high)
{
    // Опорный элемент (принимаем за опорный последний элемент)
    int pivot = tempData[high];
    int i = (low - 1); // Индекс меньшего элемента

    for (int j = low; j <= high - 1 && isSorting; j++)
    {
        // Если текущий элемент меньше или равен опорному
        if (tempData[j] <= pivot)
        {
            i++; // увеличиваем индекс меньшего элемента
            std::swap(tempData[i], tempData[j]);
        }
    }
    std::swap(tempData[i + 1], tempData[high]);
    return (i + 1);
}

void MainWindow::mergeSort(int left, int right)
{
    if (left < right && isSorting)
    {
        int mid = left + (right - left) / 2;

        // Сортируем первую и вторую половины
        mergeSort(left, mid);
        mergeSort(mid + 1, right);

        merge(left, mid, right);
    }
}

void MainWindow::mergeSortTimer(int left, int right)
{
    if (left < right && isSorting)
    {
        int mid = left + (right - left) / 2;

        // Сортируем первую и вторую половины
        mergeSortTimer(left, mid);
        mergeSortTimer(mid + 1, right);

        mergeTimer(left, mid, right);
    }
}

void MainWindow::merge(int left, int mid, int right)
{
    int i, j, k;
    int n1 = mid - left + 1;
    int n2 = right - mid;

    // Создаем временные массивы
    int L[n1], R[n2];

    // Копируем данные во временные массивы L[] и R[]
    for (i = 0; i < n1; i++)
        L[i] = m_data[left + i];
    for (j = 0; j < n2; j++)
        R[j] = m_data[mid + 1 + j];

    // Сливаем временные массивы обратно в m_data[left..right]
    i = 0; // Индекс первого подмассива
    j = 0; // Индекс второго подмассива
    k = left; // Индекс сливаемого подмассива
    while (i < n1 && j < n2 && isSorting)
    {
        if (L[i] <= R[j])
        {
            m_data[k] = L[i];
            i++;
        }
        else
        {
            m_data[k] = R[j];
            j++;
        }
        delay(50);  // Задержка в 50 миллисекунд
        update();
        k++;
    }

    // Копируем оставшиеся элементы L[], если есть
    while (i < n1 && isSorting)
    {
        m_data[k] = L[i];
        i++;
        k++;
        delay(50);  // Задержка в 50 миллисекунд
        update();
    }

    // Копируем оставшиеся элементы R[], если есть
    while (j < n2 && isSorting)
    {
        m_data[k] = R[j];
        j++;
        k++;
        delay(50);  // Задержка в 50 миллисекунд
        update();
    }
}

void MainWindow::mergeTimer(int left, int mid, int right)
{
    int i, j, k;
    int n1 = mid - left + 1;
    int n2 = right - mid;

    // Создаем временные массивы
    int L[n1], R[n2];

    // Копируем данные во временные массивы L[] и R[]
    for (i = 0; i < n1; i++)
        L[i] = tempData[left + i];
    for (j = 0; j < n2; j++)
        R[j] = tempData[mid + 1 + j];

    // Сливаем временные массивы обратно в tempData[left..right]
    i = 0; // Индекс первого подмассива
    j = 0; // Индекс второго подмассива
    k = left; // Индекс сливаемого подмассива
    while (i < n1 && j < n2 && isSorting)
    {
        if (L[i] <= R[j])
        {
            tempData[k] = L[i];
            i++;
        }
        else
        {
            tempData[k] = R[j];
            j++;
        }
        k++;
    }

    // Копируем оставшиеся элементы L[], если есть
    while (i < n1 && isSorting)
    {
        tempData[k] = L[i];
        i++;
        k++;
    }

    // Копируем оставшиеся элементы R[], если есть
    while (j < n2 && isSorting)
    {
        tempData[k] = R[j];
        j++;
        k++;
    }
}

void MainWindow::interpolationSort()
{
    if (!isSorting) return;

    std::vector<int> divideSize;
    int end = m_size;
    divideSize.push_back(end);

    while (!divideSize.empty() && isSorting) {
        int size = divideSize.back();
        divideSize.pop_back();
        int start = end - size;
        int min = m_data[start];
        int max = m_data[start];

        for (int i = start + 1; i < end && isSorting; i++) {
            if (m_data[i] < min) {
                min = m_data[i];
            }
            else if (m_data[i] > max) {
                max = m_data[i];
            }
        }

        if (min == max) {
            end -= size;
        }
        else {
            int p = 0;
            std::vector<std::vector<int>> bucket(size);
            for (int i = start; i < end && isSorting; i++) {
                p = static_cast<int>(((m_data[i] - min) / static_cast<double>(max - min)) * (size - 1));
                bucket[p].push_back(m_data[i]);
            }

            for (int i = 0; i < size && isSorting; i++) {
                if (!bucket[i].empty()) {
                    for (int j = 0; j < bucket[i].size() && isSorting; j++) {
                        m_data[start++] = bucket[i][j];
                        delay(50);  // Задержка в 50 миллисекунд
                        update();
                    }
                    divideSize.push_back(bucket[i].size());
                }
            }
        }
    }
}

void MainWindow::interpolationSortTimer()
{
    if (!isSorting) return;

    std::vector<int> divideSize;
    int end = m_size;
    divideSize.push_back(end);

    while (!divideSize.empty() && isSorting) {
        int size = divideSize.back();
        divideSize.pop_back();
        int start = end - size;
        int min = tempData[start];
        int max = tempData[start];

        for (int i = start + 1; i < end && isSorting; i++) {
            if (tempData[i] < min) {
                min = tempData[i];
            }
            else if (tempData[i] > max) {
                max = tempData[i];
            }
        }

        if (min == max) {
            end -= size;
        }
        else {
            int p = 0;
            std::vector<std::vector<int>> bucket(size);
            for (int i = start; i < end && isSorting; i++) {
                p = static_cast<int>(((tempData[i] - min) / static_cast<double>(max - min)) * (size - 1));
                bucket[p].push_back(tempData[i]);
            }

            for (int i = 0; i < size && isSorting; i++) {
                if (!bucket[i].empty()) {
                    for (int j = 0; j < bucket[i].size() && isSorting; j++) {
                        tempData[start++] = bucket[i][j];
                    }
                    divideSize.push_back(bucket[i].size());
                }
            }
        }
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
    int elapsedTime;
    isSorting = true;

    if (ui->comboBox->currentIndex() == 0) {
        timer.start();
        heapSortTimer();
        elapsedTime = timer.nsecsElapsed();
        ui->time->setText("Скорость: "+QString::number(elapsedTime / 1000000000.0, 'f', 9)+" секунды");

        heapSort();
    } else if (ui->comboBox->currentIndex() == 1) {
        timer.start();
        quickSortTimer(0, m_size - 1);
        elapsedTime = timer.nsecsElapsed();
        ui->time->setText("Скорость: "+QString::number(elapsedTime / 1000000000.0, 'f', 9)+" секунды");

        quickSort(0, m_size - 1);
    } else if (ui->comboBox->currentIndex() == 2) {
        timer.start();
        mergeSortTimer(0, m_size - 1);
        elapsedTime = timer.nsecsElapsed();
        ui->time->setText("Скорость: "+QString::number(elapsedTime / 1000000000.0, 'f', 9)+" секунды");
        mergeSort(0, m_size - 1);
    } else {
        timer.start();
        interpolationSortTimer();
        elapsedTime = timer.nsecsElapsed();
        ui->time->setText("Скорость: "+QString::number(elapsedTime / 1000000000.0, 'f', 9)+" секунды");
        interpolationSort();
    }


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

