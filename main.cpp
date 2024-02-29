#include <iostream>
#include "RBTree.h"
using namespace std;
int main() {
    RBTree tree;

    cout << "-----------------INSERTANDO------------------" << endl;
    cout << "----CASO 1:----" << endl;

    tree.insertValue(10);
    tree.insertValue(20);
    tree.insertValue(30);
    tree.insertValue(35);

    cout << "Inorder traversal:" << endl;
    tree.inorder();
    /*
    /*cout << "----CASO 2:----" << endl;

    tree.insertValue(20);
    tree.insertValue(30);
    tree.insertValue(35);
    cout << "Inorder traversal:" << endl;
    tree.inorder();
     */
/*
    cout << "----CASO 3:----" << endl;

    tree.insertValue(20);
    tree.insertValue(30);
    tree.insertValue(25);
    cout << "Inorder traversal:" << endl;
    tree.inorder();
     */

    cout << "-----------------ELIMINANDO------------------" << endl;
    tree.insertValue(8);
    tree.insertValue(5);
    tree.insertValue(15);
    tree.insertValue(12);
    tree.insertValue(19);
    tree.insertValue(9);
    tree.insertValue(13);
    tree.insertValue(23);
    tree.insertValue(10);
    cout << "Borrando nodo 19..." << endl;
    tree.deleteValue(19);
    tree.inorder();
    cout << "Insertando 1..." << endl;
    tree.insertValue(1);
    tree.inorder();
    cout << "Borrando nodo 5....."<< endl;
    tree.deleteValue(5);
    cout << "Inorder traversal after deletion:" << endl;
    tree.inorder();

    cout << "Borrando nodo 12....."<< endl;
    tree.deleteValue(12);
    cout << "Inorder traversal after deletion:" << endl;
    tree.inorder();


    cout << "-----------------BUSCANDO------------------" << endl;

    tree.searchValue(25);

    // Test case 2

    tree = RBTree();
    cout << "Test case 2:" << endl;
    tree.insertValue(3);
    tree.insertValue(1);
    tree.insertValue(5);
    tree.insertValue(7);
    cout << "Inorder traversal:" << endl;
    tree.inorder();
    cout<< "agreguemos el 6" << endl;
    tree.insertValue(6);
    tree.inorder();
    cout<< "Agreguemos el 8"<< endl;
    tree.insertValue(8);
    cout<<"agregamos el 9"<< endl;
    tree.insertValue(9);
    tree.inorder();


}