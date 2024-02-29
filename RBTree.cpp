#include <bits/stdc++.h>
#include "RBTree.h"
using namespace std;

Node::Node(int data) {//Constructor de la clase Node.
    this->data = data;//
    color = RED;//Inicializa el nodo con el dato proporcionado y el color rojo (RED).
    left = right = parent = nullptr;//Inicializa los punteros left, right, y parent como nullptr.
}

RBTree::RBTree() {//Constructor de la clase RBTree.
    root = nullptr;//Inicializa el puntero root como nullptr, indicando que el árbol está vacío.
}

int RBTree::getColor(Node *&node) {
    if (node == nullptr)
        return BLACK;//Si el nodo es nullptr, devuelve BLACK

    return node->color;//Retorna el color de un nodo.
}

void RBTree::setColor(Node *&node, int color) {
    if (node == nullptr)
        return;//Si el nodo es nullptr, no hace nada.

    node->color = color;//Si no, establece el color del nodo.
}

Node* RBTree::insert(Node *&root, Node *&ptr) {
    if (root == nullptr)
        return ptr;

    if (ptr->data < root->data) {
        root->left = insert(root->left, ptr);//Utiliza recursión para encontrar la posición adecuada para insertar el nodo.
        root->left->parent = root;
    } else if (ptr->data > root->data) {
        root->right = insert(root->right, ptr);
        root->right->parent = root;//Utiliza recursión para encontrar la posición adecuada para insertar el nodo.
    }

    return root;
}

void RBTree::insertValue(int n) {
    Node *node = new Node(n);//Crea un nuevo nodo con el valor proporcionado.
    root = insert(root, node);//Llama a insert para insertar el nodo en el árbol.
    fixInsertRBTree(node);//Llama a fixInsertRBTree para corregir cualquier violación de las propiedades del árbol Red-Black.
}
/*Realiza una rotación a la izquierda alrededor del nodo dado.
Actualiza los punteros del árbol y sus padres según sea necesario.
 * */
void RBTree::rotateLeft(Node *&ptr) {
    Node *right_child = ptr->right;
    ptr->right = right_child->left;

    if (ptr->right != nullptr)
        ptr->right->parent = ptr;

    right_child->parent = ptr->parent;

    if (ptr->parent == nullptr)
        root = right_child;
    else if (ptr == ptr->parent->left)
        ptr->parent->left = right_child;
    else
        ptr->parent->right = right_child;

    right_child->left = ptr;
    ptr->parent = right_child;
}
/*Realiza una rotación a la derecha alrededor del nodo dado.
Actualiza los punteros del árbol y sus padres según sea necesario.
 * */
void RBTree::rotateRight(Node *&ptr) {
    Node *left_child = ptr->left;
    ptr->left = left_child->right;

    if (ptr->left != nullptr)
        ptr->left->parent = ptr;

    left_child->parent = ptr->parent;

    if (ptr->parent == nullptr)
        root = left_child;
    else if (ptr == ptr->parent->left)
        ptr->parent->left = left_child;
    else
        ptr->parent->right = left_child;

    left_child->right = ptr;
    ptr->parent = left_child;
}
/*Corrige las violaciones de las propiedades del árbol Red-Black después de la inserción de un nuevo nodo.
Realiza rotaciones y ajustes de colores según sea necesario para restaurar las propiedades del árbol.
 * */
void RBTree::fixInsertRBTree(Node *&ptr) {
    Node *parent = nullptr;
    Node *grandparent = nullptr;
    while (ptr != root && getColor(ptr) == RED && getColor(ptr->parent) == RED) {
        parent = ptr->parent;
        grandparent = parent->parent;
        if (parent == grandparent->left) {
            Node *uncle = grandparent->right;
            if (getColor(uncle) == RED) {
                setColor(uncle, BLACK);
                setColor(parent, BLACK);
                setColor(grandparent, RED);
                ptr = grandparent;
            } else {
                if (ptr == parent->right) {
                    rotateLeft(parent);
                    ptr = parent;
                    parent = ptr->parent;
                }
                rotateRight(grandparent);
                swap(parent->color, grandparent->color);
                ptr = parent;
            }
        } else {
            Node *uncle = grandparent->left;
            if (getColor(uncle) == RED) {
                setColor(uncle, BLACK);
                setColor(parent, BLACK);
                setColor(grandparent, RED);
                ptr = grandparent;
            } else {
                if (ptr == parent->left) {
                    rotateRight(parent);
                    ptr = parent;
                    parent = ptr->parent;
                }
                rotateLeft(grandparent);
                swap(parent->color, grandparent->color);
                ptr = parent;
            }
        }
    }
    setColor(root, BLACK);
}
/*Corrige las violaciones de las propiedades del árbol Red-Black después de la eliminación de un nuevo nodo.
Realiza rotaciones y ajustes de colores según sea necesario para restaurar las propiedades del árbol.*/
void RBTree::fixDeleteRBTree(Node *&node) {
    if (node == nullptr)
        return;

    if (node == root) {
        root = nullptr;
        return;
    }

    if (getColor(node) == RED || getColor(node->left) == RED || getColor(node->right) == RED) {
        Node *child = node->left != nullptr ? node->left : node->right;

        if (node == node->parent->left) {
            node->parent->left = child;
            if (child != nullptr)
                child->parent = node->parent;
            setColor(child, BLACK);
            delete (node);
        } else {
            node->parent->right = child;
            if (child != nullptr)
                child->parent = node->parent;
            setColor(child, BLACK);
            delete (node);
        }
    } else {
        Node *sibling = nullptr;
        Node *parent = nullptr;
        Node *ptr = node;
        setColor(ptr, DOUBLE_BLACK);
        while (ptr != root && getColor(ptr) == DOUBLE_BLACK) {
            parent = ptr->parent;
            if (ptr == parent->left) {
                sibling = parent->right;
                if (getColor(sibling) == RED) {
                    setColor(sibling, BLACK);
                    setColor(parent, RED);
                    rotateLeft(parent);
                } else {
                    if (getColor(sibling->left) == BLACK && getColor(sibling->right) == BLACK) {
                        setColor(sibling, RED);
                        if(getColor(parent) == RED)
                            setColor(parent, BLACK);
                        else
                            setColor(parent, DOUBLE_BLACK);
                        ptr = parent;
                    } else {
                        if (getColor(sibling->right) == BLACK) {
                            setColor(sibling->left, BLACK);
                            setColor(sibling, RED);
                            rotateRight(sibling);
                            sibling = parent->right;
                        }

                        setColor(sibling, parent->color);
                        setColor(parent, BLACK);
                        setColor(sibling->right, BLACK);
                        rotateLeft(parent);
                        break;
                    }
                }
            } else {
                sibling = parent->left;
                if (getColor(sibling) == RED) {
                    setColor(sibling,BLACK);
                    setColor(parent, RED);
                    rotateRight(parent);
                } else {
                    if (getColor(sibling->left) == BLACK && getColor(sibling->right) == BLACK) {
                        setColor(sibling, RED);
                        if (getColor(parent) == RED)
                            setColor(parent, BLACK);
                        else
                            setColor(parent, DOUBLE_BLACK);
                        ptr = parent;
                    } else {
                        if (getColor(sibling->left) == BLACK) {
                            setColor(sibling->right, BLACK);
                            setColor(sibling, RED);
                            rotateLeft(sibling);
                            sibling = parent->left;
                        }
                        setColor(sibling, parent->color);
                        setColor(parent, BLACK);
                        setColor(sibling->left, BLACK);
                        rotateRight(parent);
                        break;
                    }
                }
            }
        }
        if (node == node->parent->left)
            node->parent->left = nullptr;
        else
            node->parent->right = nullptr;
        delete(node);
        setColor(root, BLACK);
    }
}
/*Función que se encarga de corregir las violaciones de las propiedades del árbol Red-Black después de la eliminación de un nodo.*/
Node* RBTree::deleteRBT(Node *&root, int data) {
    if (root == nullptr)
        return root;

    if (data < root->data)
        return deleteRBT(root->left, data);

    if (data > root->data)
        return deleteRBT(root->right, data);

    if (root->left == nullptr || root->right == nullptr)
        return root;

    Node *temp = minValueNode(root->right);
    root->data = temp->data;
    return deleteRBT(root->right, temp->data);
}

void RBTree::deleteValue(int data) {
    Node *node = deleteRBT(root, data);
    fixDeleteRBTree(node);
}

void RBTree::inorder(Node *&ptr) {
    if (ptr == nullptr)
        return;

    inorder(ptr->left);
    cout << ptr->data << " ";
    if (ptr->color == RED)
        cout << "ROJO" << endl;
    else
        cout << "NEGRO" << endl;
    inorder(ptr->right);
}

void RBTree::inorder() {
    inorder(root);
}

void RBTree::preorder(Node *&ptr) {
    if (ptr == nullptr)
        return;

    if (ptr->color == RED)
        cout << ptr->data << " ROJO" << endl;
    else
        cout << ptr->data << " NEGRO" << endl;

    preorder(ptr->left);
    preorder(ptr->right);
}
void RBTree::preorder() {
    preorder(root);
    cout << "-------" << endl;
}
Node *RBTree::search(Node *& node, int value){
    if (node == nullptr)
        return nullptr;
    if(node-> data == value)
        return node;
    if(value< node-> data)
        return search(node-> left, value);
    else
        return search(node-> right, value);

}
void RBTree::searchValue(int value){
    Node *result = search(root, value);
    if (result != nullptr)
        cout << "El valor " << value << " se encontro en el arbol." << endl;
    else
        cout << "El valor " << value << " no se encontro en el arbol." << endl;
}
Node *RBTree::minValueNode(Node *&node) {

    Node *ptr = node;

    while (ptr->left != nullptr)
        ptr = ptr->left;

    return ptr;
}



