#ifndef BINARY_TREE_HPP
#define BINARY_TREE_HPP
using std::cout;
#include <iostream>

template <typename Type>
struct Node {
    Type item{};
    Node<Type>* left{ nullptr };
    Node<Type>* right{ nullptr };

};

template <typename Type>
class BinaryTree {
public:
    BinaryTree() {}
    BinaryTree(const BinaryTree<Type>& objToCopy);
    BinaryTree<Type>& operator=(const BinaryTree& b);
    ~BinaryTree();
    void insert(Type item);
    void preOrder(std::ostringstream&);
    void inOrder(std::ostringstream&);
    void postOrder(std::ostringstream&);
    int nodeCount();
    Node<Type>* find(Type item);
    Node<Type>* findRightMostNode(Node<Type>* find);
    void remove(Type item);
    int  height();
    int leavesCount();


protected:
    Node<Type>* root{ nullptr };

private:
    void destroy(Node<Type>* curr);
    void copyTree(Node<Type>* curr);
    void insert(Type item, Node<Type>* curr);
    void preOrder(Node<Type>* curr);
    void postOrder(Node<Type>* curr);
    void inOrder(Node<Type>* curr, std::ostringstream& out);
    int nodeCount(Node<Type>* curr);
    int leavesCount(Node<Type>* curr);
    Node<Type>* find(Type item, Node<Type>* curr);
    Node<Type>* remove(Type item, Node<Type>* curr);
    int height(int level, Node<Type>* curr);
};

template <typename Type>
BinaryTree<Type>::~BinaryTree() {
    destroy(root);
}

template <typename Type>
BinaryTree<Type>::BinaryTree(const BinaryTree<Type>& b) {
    copyTree(b.root);
}

template <class Type>
void BinaryTree<Type>::copyTree(Node<Type>* curr) {
    if (curr) {
        insert(curr->item);
        copyTree(curr->left);
        copyTree(curr->right);
    }
}

template <typename Type>
BinaryTree<Type>& BinaryTree<Type>::operator=(const BinaryTree<Type>& b) {
    copyTree(b.root);
    return *this;
}

template <typename Type>
void BinaryTree<Type>::destroy(Node<Type>* curr) {
    if (curr != nullptr) {
        destroy(curr->left);
        destroy(curr->right);
        delete curr;
    }
}

template <typename Type>
void BinaryTree<Type>::insert(Type item) {
    if (root == nullptr) {
        root = new Node<Type>(item);
        //root->item = item;
        //root->left = nullptr;
        //root->right = nullptr;
    }
    else {
        insert(item, root);
    }
}

template <typename Type>
void BinaryTree<Type>::insert(Type item, Node<Type>* curr) {
    if (item < curr->item) {
        if (curr->left == nullptr) {
            auto temp = new Node<Type>(item);
            //temp->item = item;
            //temp->right = nullptr;
           // temp->left = nullptr;
            curr->left = temp;
        }
        else {
            insert(item, curr->left);
        }
    }
    else {
        if (curr->right == nullptr) {
            auto temp = new Node<Type>(item);
            //temp->item = item;
            //temp->right = nullptr;
            //temp->left = nullptr;
            curr->right = temp;
        }
        else {
            insert(item, curr->right);
        }
    }
}

template <typename Type>
void BinaryTree<Type>::preOrder(std::ostringstream& out) {
    std::cout << "Pre Order: ";
    preOrder(root);
}

template <typename Type>
void BinaryTree<Type>::preOrder(Node<Type>* curr) {
    if (curr) {
        std::cout << curr->item << " ";
        preOrder(curr->left);
        preOrder(curr->right);
    }
}

template <class Type>
void BinaryTree<Type>::inOrder(std::ostringstream& out) {
    std::cout << "In Order: ";
    inOrder(root, out);
}

template <class Type>
void BinaryTree<Type>::inOrder(Node<Type>* curr, std::ostringstream& out) {
    if (curr) {
        inOrder(curr->left, out);
        if (out.tellp() != 0) {  // Check if we are not at the beginning of the output
            out << " ";
        }
        out << curr->item; 
        inOrder(curr->right, out);
    }

}

template <typename Type>
void BinaryTree<Type>::postOrder(std::ostringstream& out) {
    std::cout << "Post Order: ";
    postOrder(root);
}

template <typename Type>
void BinaryTree<Type>::postOrder(Node<Type>* curr) {
    if (curr) {
        postOrder(curr->left);
        postOrder(curr->right);
        std::cout << curr->item << " ";
    }
}

template <typename Type>
int BinaryTree<Type>::nodeCount() {
    return nodeCount(root);
}

template <typename Type>
int BinaryTree<Type>::nodeCount(Node<Type>* curr) {
    if (curr == nullptr) {
        return 0;
    }
    return 1 + nodeCount(curr->left) + nodeCount(curr->right);
}

template <typename Type>
int BinaryTree<Type>::leavesCount() {
    return leavesCount(root);
}

template <typename Type>
int BinaryTree<Type>::leavesCount(Node<Type>* curr) {
    if (curr == nullptr) {
        return 0;
    }
    if (curr->left == nullptr && curr->right == nullptr) {
        return 1;
    }
    return leavesCount(curr->left) + leavesCount(curr->right);
}

template <typename Type>
Node<Type>* BinaryTree<Type>::find(Type item) {
    return find(item, root);
}

template <typename Type>
Node<Type>* BinaryTree<Type>::find(Type item, Node<Type>* curr) {
    if (curr == nullptr || curr->item == item) {
        return curr;
    }
    if (item < curr->item) {
        return find(item, curr->left);
    }
    else {
        return find(item, curr->right);
    }
}

template <typename Type>
Node<Type>* BinaryTree<Type>::findRightMostNode(Node<Type>* curr) {
    if (curr == nullptr) {
        return nullptr;
    }
    while (curr->right != nullptr) {
        curr = curr->right;
    }
    return curr;
}

template <typename Type>
void BinaryTree<Type>::remove(Type item) {
    root = remove(item, root);
}

template <typename Type>
Node<Type>* BinaryTree<Type>::remove(Type item, Node<Type>* curr) {
    if (curr == nullptr) {
        return nullptr;
    }
    if (item < curr->item) {
        curr->left = remove(item, curr->left);
    }
    else if (item > curr->item) {
        curr->right = remove(item, curr->right);
    }
    else {
        if (curr->left == nullptr && curr->right == nullptr) {
            delete curr;
            return nullptr;
        }
        else if (curr->left == nullptr) {
            auto temp = curr->right;
            delete curr;
            return temp;
        }
        else if (curr->right == nullptr) {
            auto temp = curr->left;
            delete curr;
            return temp;
        }
        else {
            auto rightmost = findRightMostNode(curr->left);
            curr->item = rightmost->item;
            curr->left = remove(rightmost->item, curr->left);
        }
    }
    return curr;
}

template <typename Type>
int BinaryTree<Type>::height() {
    return height(0, root);
}

template <typename Type>
int BinaryTree<Type>::height(int level, Node<Type>* curr) {
    if (curr == nullptr) {
        return level - 1;
    }
    auto leftHeight = height(level+1, curr->left);
    auto rightHeight = height(level+1, curr->right);
    return std::max(leftHeight, rightHeight);
}


#endif // BINARY_TREE_HPP