#include "AVLTree.h"
#include<iomanip>

int AVLTree::dataLength = 8;

AVLTree::nodePointer AVLTree::rotateLL(nodePointer & thisNode) {
    nodePointer leftChild = thisNode->left;
    thisNode->left = leftChild->right;
    leftChild->right = thisNode;// Make leftChild current node.

    // Update current node's right child's height first.
    thisNode->height = max(getHeight(thisNode->left), getHeight(thisNode->right)) + 1;
    // Update current node's height.
    leftChild->height = max(getHeight(leftChild->left), getHeight(thisNode)) + 1;

    return leftChild;// leftChild now is current node.
}

AVLTree::nodePointer AVLTree::rotateRR(nodePointer & thisNode) {
    nodePointer rightChild = thisNode->right;
    thisNode->right = rightChild->left;
    rightChild->left = thisNode;// Make rightChild current node.

    // Update current node's left child's height first.
    thisNode->height = max(getHeight(thisNode->left), getHeight(thisNode->right)) + 1;
    // Update current node's height.
    rightChild->height = max(getHeight(thisNode), getHeight(rightChild->right)) + 1;

    return rightChild;// rightChild now is current node.
}

AVLTree::nodePointer AVLTree::rotateLR(nodePointer & thisNode) {
    thisNode->left = rotateRR(thisNode->left);
    return rotateLL(thisNode);
}

AVLTree::nodePointer AVLTree::rotateRL(nodePointer & thisNode) {
    thisNode->right = rotateLL(thisNode->right);
    return rotateRR(thisNode);
}

int AVLTree::getHeight(nodePointer thisNode) {
    return (thisNode == nullptr ? -1 : thisNode->height);
}

short int AVLTree::getBalanceFactor(nodePointer thisNode) {
    if (thisNode == nullptr) {
        return 0;
    } else {
        return getHeight(thisNode->left) - getHeight(thisNode->right);
    }
}

int AVLTree::max(int left, int right) {
    return (left > right ? left : right);
}

AVLTree::nodePointer AVLTree::pushBackAux(DataType& item, nodePointer thisNode) {
    if (thisNode == nullptr) {// Vacancy found.
        thisNode = new Node(item);
    } else if (item < thisNode->data) {// Into left subtree.

        thisNode->left = pushBackAux(item, thisNode->left);

        if (getBalanceFactor(thisNode) == 2) {// Unbalanced!
            if (item < thisNode->left->data) {// LL Rotate
                thisNode = rotateLL(thisNode);
            } else {// LR Rotate
                thisNode = rotateLR(thisNode);
            }
        }
    } else if (item > thisNode->data) {// Into right subtree.

        thisNode->right = pushBackAux(item, thisNode->right);

        if (getBalanceFactor(thisNode) == -2) {// Unbalanced!
            if (item > thisNode->right->data) {// RR Rotate
                thisNode = rotateRR(thisNode);
            } else {// RL Rotate
                thisNode = rotateRL(thisNode);
            }
        }
    }

    thisNode->height = max(getHeight(thisNode->left), getHeight(thisNode->right)) + 1;// Update height.

    return thisNode;
}

AVLTree::nodePointer AVLTree::findMinNode(nodePointer thisNode) {
    if (thisNode == nullptr) {
        return nullptr;
    } else if (thisNode->left == nullptr) {// MinNode found.
        return thisNode;
    } else {// thisNode has left subtree.
        return findMinNode(thisNode->left);
    }
}

AVLTree::nodePointer AVLTree::popAux(DataType& item, nodePointer thisNode) {

    nodePointer temp;// It's just a temporary node pointer.

    if (thisNode == nullptr) {// Item not found.
        return nullptr;
    } else if (item < thisNode->data) {// Into left subtree.
        thisNode->left = popAux(item, thisNode->left);
    } else if (item > thisNode->data) {// Into right subtree.
        thisNode->right = popAux(item, thisNode->right);
    } else {// Item found.
        if (thisNode->left && thisNode->right) {// With 2 children.
            temp = findMinNode(thisNode->right);// Find successor node of thisNode.
            thisNode->data = temp->data;
            thisNode->right = popAux(temp->data, thisNode->right);
        } else {// With 0 or 1 child.
            temp = thisNode;
            if (thisNode->left == nullptr) {
                thisNode = thisNode->right;
            } else if (thisNode->right == nullptr) {
                thisNode = thisNode->left;
            }
            delete temp;
            temp = nullptr;
        }
    }
    // Extra step - with 0 child case.
    if (thisNode == nullptr) {
        return thisNode;
    }

    // Update height.
    thisNode->height = max(getHeight(thisNode->left), getHeight(thisNode->right)) + 1;

    // If thisNode is unbalanced.
    if (getBalanceFactor(thisNode) == 2) {// Left subtree is higher than the right one.
        if (getBalanceFactor(thisNode->left) == -1) {
            // LR Rotate
            thisNode = rotateLR(thisNode);
        } else {// getBalanceFactor(thisNode->left) == 1
            // LL Rotate
            thisNode = rotateLL(thisNode);
        }
    } else if (getBalanceFactor(thisNode) == -2) {// Right subtree is higher than the left one.
        if (getBalanceFactor(thisNode->right) == 1) {
            // RL Rotate
            thisNode = rotateRL(thisNode);
        } else {// getBalanceFactor(thisNode->right) == -1
            // RR Rotate
            thisNode = rotateRR(thisNode);
        }
    }

    return thisNode;
}

AVLTree::AVLTree() {
    root = nullptr;
}


AVLTree::~AVLTree() {
    makeEmptyAux(root);
}

void AVLTree::pushBack(DataType item) {
    root = pushBackAux(item, root);
}

void AVLTree::pop(DataType item) {
    root = popAux(item, root);
}

bool AVLTree::isEmpty() {
    return (root == nullptr);
}

void AVLTree::makeEmpty() {
    makeEmptyAux(root);
}

void AVLTree::graphOut(ostream& out) {
    graphOutAux(out, dataLength, root);
}

void AVLTree::setDataLengthForDisplay(int _dataLength) {
    dataLength = _dataLength;
}

bool AVLTree::isExisted(const DataType & item) {
    return isExistedAux(item, root);
}

bool AVLTree::isExisted(string & username) {
    return isExistedAux(username, root);
}

void AVLTree::inorderOut(ostream & out) {
    inorderOutAux(out, root);
}

DataType & AVLTree::find(DataType & item) {
    return findAux(item, root);
}

void AVLTree::makeEmptyAux(nodePointer thisNode) {
    if (thisNode == nullptr) {
        return;
    } else {
        makeEmptyAux(thisNode->left);
        makeEmptyAux(thisNode->right);
        delete thisNode;
        thisNode = nullptr;
    }
}

void AVLTree::graphOutAux(ostream& out, int indent, nodePointer thisNode) {
    if (thisNode == nullptr) {
        out << setw(indent + 1) << "#" << endl;
        return;
    }
    graphOutAux(out, indent + dataLength, thisNode->right);
    out << setw(indent) << " " << thisNode->data << endl;
    graphOutAux(out, indent + dataLength, thisNode->left);
}

bool AVLTree::isExistedAux(const DataType & item, nodePointer thisNode) {
    if (thisNode == nullptr) {// item not found
        return false;
    } else if (item < thisNode->data) {// Into left subtree.
        return isExistedAux(item, thisNode->left);
    } else if (item > thisNode->data) {// Into right subtree.
        return isExistedAux(item, thisNode->right);
    } else if (item == thisNode->data) {// item found
        return true;
    }
    return false;
}

bool AVLTree::isExistedAux(string & username, nodePointer thisNode) {
    // Here is the place where User class's method is used in AVLTree class.
    if (thisNode == nullptr) {// User not found.
        return false;
    } else if (username < thisNode->data.getUsername()) {// Into left subtree.
        return isExistedAux(username, thisNode->left);
    } else if (username > thisNode->data.getUsername()) {// Into right subtree.
        return isExistedAux(username, thisNode->right);
    } else {// User exits.
        return true;
    }
}

DataType & AVLTree::findAux(DataType & item, nodePointer thisNode) {
    if (thisNode == nullptr) {// Item not found.
        return item;
    } else if (item < thisNode->data) {// Into left subtree.
        return findAux(item, thisNode->left);
    } else if (item > thisNode->data) {// Into right subtree.
        return findAux(item, thisNode->right);
    } else {// Item found.
        return thisNode->data;
    }
}

void AVLTree::inorderOutAux(ostream & out, nodePointer & thisNode) {
    if (thisNode == nullptr) {
        return;
    } else {
        inorderOutAux(out, thisNode->left);
        thisNode->data.displayAll(out);// Here is the place where User class's method is used in AVLTree class.
        out << endl;
        inorderOutAux(out, thisNode->right);
    }
}
