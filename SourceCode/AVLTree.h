#include<iostream>
#include"User.h"// Used in inorderOut(), inorderOutAux(), isExisted() and isExistedAux()!

#pragma once

using namespace std;
typedef User DataType;

class AVLTree {
private:

    class Node {
    public:
        DataType data;
        int height;
        Node* left;
        Node* right;

        Node(DataType _data) : data(_data), height(0), left(nullptr), right(nullptr) {}
    };
    typedef Node* nodePointer;

    // This member is used in method graphOut and graphOutAux.
    // Initialized with 8.
    static int dataLength;

    nodePointer root;

    nodePointer rotateLL(nodePointer& thisNode);
    nodePointer rotateRR(nodePointer& thisNode);
    nodePointer rotateLR(nodePointer& thisNode);
    nodePointer rotateRL(nodePointer& thisNode);
    nodePointer pushBackAux(DataType& item, nodePointer thisNode);
    nodePointer popAux(DataType& item, nodePointer thisNode);

    // If thisNode == nullptr, return -1, 
    // else return thisNode's height.
    int getHeight(nodePointer thisNode);

    // Return (left child's height - right child's height).
    // If thisNode == nullptr, return 0.
    short int getBalanceFactor(nodePointer thisNode);

    // Return the greater one between left and right.
    int max(int left, int right);

    // Find min node, thisNode included.
    // If thisNode == nullptr, return nullptr.
    nodePointer findMinNode(nodePointer thisNode);

    // Auxiliary method of makeEmpty().
    void makeEmptyAux(nodePointer thisNode);

    // Auxiliary method of isExisted().
    bool isExistedAux(const DataType& item, nodePointer thisNode);
    // * Method getUsername() of *User* class is used in this method!
    bool isExistedAux(string& username, nodePointer thisNode);

    // Auxiliary method of find().
    DataType& findAux(DataType& item, nodePointer thisNode);

    // Auxiliary method of graphOut().
    void graphOutAux(ostream& out, int indent, nodePointer thisNode);

    // Auxiliary method of inorderOut().
    // * Method displayAll(out) of *User* class is used in this method!
    void inorderOutAux(ostream& out, nodePointer& thisNode);
public:
    AVLTree();
    ~AVLTree();

    // Insert item in the tree.
    void pushBack(DataType item);

    // Delete item from the tree.
    void pop(DataType item);

    // Is the tree empty?
    bool isEmpty();

    // Empty the whole tree.
    void makeEmpty();

    // Set date length for graph output.
    void setDataLengthForDisplay(int _dataLength);

    // Does item exit in the tree?
    bool isExisted(const DataType& item);

    // Does username exit in the tree?
    // * Method getUsername() of *User* class is used in this method!
    bool isExisted(string& username);

    // Graphic output.
    void graphOut(ostream& out);

    // Inoreder output.
    // * Method displayAll(out) of *User* class is used in this method!
    void inorderOut(ostream& out);

    // Make sure item exists, or it will the reference of parameter item.
    DataType& find(DataType& item);
};