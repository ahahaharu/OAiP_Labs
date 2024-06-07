#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->treeWidget->setColumnCount(1);
    ui->treeWidget->setHeaderLabel("Дерево");
    beginItem = new QTreeWidgetItem(ui->treeWidget);

    ui->comboBox->addItems({"Прямой обход", "Обратный обход", "Симметричный обход (по возрастанию ключей)"});

    updateTree();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::updateTree()
{
    ui->treeWidget->clear();

    beginItem = new QTreeWidgetItem(ui->treeWidget);
    beginItem->setText(0, " ");
    tree.fillTreeWidget(beginItem, tree.root);

    ui->treeWidget->expandAll();
}

void MainWindow::on_insertButton_clicked()
{
    tree.insert(ui->keyInsert->value(), ui->valueInsert->text());
    updateTree();

    ui->status->setText("Элемент с ключом " + QString::number(ui->keyInsert->value()) + " добавлен в дерево с балансировкой.");

    ui->valueInsert->clear();
}


void MainWindow::on_removeButton_clicked()
{
    Node<int, QString>* foundedNode = tree.search(ui->keyInsert->value());
    if(foundedNode == nullptr) ui->status->setText("Элемента с ключом " + QString::number(ui->keyInsert->value()) + " не найден.");
    else ui->status->setText("Элемент с ключом " + QString::number(ui->keyInsert->value()) + " удален с балансировкой.");

    tree.root = tree.remove(ui->keyInsert->value());
    updateTree();
}


void MainWindow::on_searchButton_clicked()
{
    Node<int, QString>* foundedNode = tree.search(ui->keyInsert->value());

    if(foundedNode != nullptr) ui->status->setText("Значение найденного по ключу элемента : '" + foundedNode->value + "'.");
    else ui->status->setText("Элемента с ключом " + QString::number(ui->keyInsert->value()) + " не найден.");
}


void MainWindow::on_printButton_clicked()
{
    ui->print->clear();
    ui->print->setText("| ");

    if(ui->comboBox->currentIndex() == 0)
    {
        tree.straightPrint(ui->print);
    }
    else if(ui->comboBox->currentIndex() == 1)
    {
        tree.reversePrint(ui->print);
    }
    else
    {
        tree.symmetricalPrint(ui->print);
    }
}


void MainWindow::on_searchButton_3_clicked()
{
    ui->getCount->setText("Кол-во листов дерева = " + QString::number(tree.leavesCount()));
}

