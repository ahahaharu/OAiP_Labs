#ifndef TREE_H
#define TREE_H

#include "node.h"
#include "node.cpp"
#include <QDebug>
#include <QTreeWidgetItem>
#include <QLabel>


template <typename T, typename U>
class Tree
{
public:

    Node<T, U>* root;

    Tree();
    Tree(std::pair<T, U> *arr, std::size_t size);

    void insert(Node<T, U> *&node, T key, U value);
    void insert(T key, U value);
    Node<T, U>* remove(Node<T, U> *&node, T key);
    Node<T, U>* remove(T key);
    Node<T, U>* search(Node<T, U>* node, T key);
    Node<T, U>* search(T key);

    Node<T, U>* getMax(Node<T, U> *&node);
    Node<T, U>* getMin(Node<T, U> *&node);

    void symmetricalPrint(QLabel* lineEdit);
    void reversePrint(QLabel *lineEdit);
    void straightPrint(QLabel *lineEdit);

    void symmetricalPrint(Node<T, U> *node, QLabel* lineEdit);
    void reversePrint(Node<T, U>* node, QLabel *lineEdit);
    void straightPrint(Node<T, U>* node, QLabel *lineEdit);


    int getHeight(Node<T, U>* node);
    void updateHeight(Node<T, U>* node);

    int getBalance(Node<T, U>* node);
    void swap (Node<T, U>* &a, Node<T, U>* &b);
    void rightRotate(Node<T, U>* &node);
    void leftRotate(Node<T, U> *&node);

    void balance(Node<T, U>* node);

    void fillTreeWidget(QTreeWidgetItem *&parent, Node<T, U>*node);

};

#endif // TREE_H
