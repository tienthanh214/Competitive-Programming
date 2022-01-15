#include <stdio.h>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <assert.h>
#include <queue>

using namespace std;

struct Node {
    int key;
    int height;
    Node* left;
    Node* right;
    Node* parent;

    Node(int value = 0) {
        this->key = value;
        this->height = 0;
        this->left = this->right = this->parent = nullptr;
    }

};

class AVLTree {
private:
    Node* root;
public:
    AVLTree();
    ~AVLTree();
public:
    void updateHeight(Node*);
    int getHeight(Node*);
    int delta(Node*);
public:
    void leftJoin(Node*, Node*);
    void rightJoin(Node*, Node*);
public:
    void rotateLeft(Node*);
    void rotateRight(Node*);
    void balance(Node*);
public:
    Node* findMax(Node*);
    Node* findMin(Node*);
    Node* findMin();
    Node* findMax();
    Node* predecessor(int);
    Node* successor(int);
public:
    Node* search(int);
    void insertKey(int);
    void deleteKey(int);
    void deleteNode(Node*);
public:
    void inOrder();
    void inOrder(Node*);
    void postOrder();
    void postOrder(Node*);
    void travel();
    void clearTree(Node*);
public:
    bool isEmpty();
};

/* ------------------- AVLTree class definition ------------------- */
AVLTree::AVLTree() {
    this->root = nullptr;
}

void AVLTree::clearTree(Node* x) {
    if (x == nullptr) return;
    clearTree(x->left);
    clearTree(x->right);
    delete x;
}

AVLTree::~AVLTree() {
    clearTree(this->root);
    this->root = nullptr;
}

bool AVLTree::isEmpty() {
    return this->root == nullptr;
}

int AVLTree::getHeight(Node* x) {
    if (x == nullptr) return 0;
    if (x->height) return x->height;
    return x->height = max(getHeight(x->left), getHeight(x->right)) + 1;
}

void AVLTree::updateHeight(Node* x) {
    if (x == nullptr) return;
    x->height = max(getHeight(x->left), getHeight(x->right)) + 1;
}

int AVLTree::delta(Node* x) {
    if (x == nullptr) return 0;
    return abs(getHeight(x->left) - getHeight(x->right));
}

void AVLTree::leftJoin(Node* x, Node* y) { // make y left child of x
    if (y != nullptr)
        y->parent = x;
    if (x == nullptr)
        this->root = y;
    else 
        x->left = y;
}

void AVLTree::rightJoin(Node* x, Node* y) { // make y right child of x
    if (y != nullptr)
        y->parent = x;
    if (x == nullptr) 
        this->root = y;
    else 
        x->right = y;
}

void AVLTree::rotateLeft(Node* x) { // rotate left subtree root x
    if (x == nullptr) return;
    Node* y = x->right;
    Node* z = x->parent;
    rightJoin(x, y->left);
    leftJoin(y, x);
    if (z == nullptr) { 
        rightJoin(z, y); // now y root
    } else if (z->left == x) {
        leftJoin(z, y);
    } else {
        rightJoin(z, y);
    }
    updateHeight(x);
    updateHeight(y);
    updateHeight(z);
}

void AVLTree::rotateRight(Node* x) {
    if (x == nullptr) return;
    Node* y = x->left;
    Node* z = x->parent;
    leftJoin(x, y->right);
    rightJoin(y, x);
    if (z == nullptr) {
        rightJoin(z, y);
    } else if (z->left == x) {
        leftJoin(z, y);
    } else {
        rightJoin(z, y);
    }
    updateHeight(x);
    updateHeight(y);
    updateHeight(z);
}

void AVLTree::balance(Node* a) {
    if (a == nullptr) return;
    if (delta(a) <= 1) return;
    // balance(a->left);
    // balance(a->right);
    if (getHeight(a->left) > getHeight(a->right)) {
        if (getHeight(a->left->left) < getHeight(a->left->right))
            rotateLeft(a->left);
        rotateRight(a);
    } else if (getHeight(a->left) < getHeight(a->right)) {
        if (getHeight(a->right->left) > getHeight(a->right->right))
            rotateRight(a->right);
        rotateLeft(a);
    }
}

void AVLTree::insertKey(int value) {
    if (this->root == nullptr) {
        this->root = new Node(value);
        return;
    }
    Node* x = root;
    Node* y = nullptr; // parent
    while (x) {
        y = x;
        x = x->key > value ? x->left : x->right;
    }

    x = new Node(value);
    if (y->key > value) 
        leftJoin(y, x);
    else 
        rightJoin(y, x);
    // balancing
    while (x != root) {
        x = x->parent;
        balance(x);
        updateHeight(x);
    }
}

Node* AVLTree::findMin(Node* x) {
    while (x->left) x = x->left;
    return x;
}

Node* AVLTree::findMax(Node* x) {
    cout << x->key << endl;
    while (x->right) x = x->right;
    return x;
}

Node* AVLTree::findMin() {
    cout << root << endl;
    findMin(root);
}

Node* AVLTree::findMax() {
    cout << root << endl;

    findMax(root);
}

Node* AVLTree::successor(int value) {
    Node* x = root;
    Node* result = nullptr;
    while (x) {
        if (x->key > value) {
            result = x;
            x = x->left;
        } else {
            x = x->right;
        }
    }
    return result;
}

Node* AVLTree::predecessor(int value) {
    Node* x = root;
    Node* result = nullptr;
    while (x) {
        if (x->key < value) {
            result = x;
            x = x->right;
        } else {
            x = x->left;
        }
    }
    return result;
}

Node* AVLTree::search(int value) {
    Node *x = root;
    while (x != NULL) {
        if (x->key == value) 
            return x;
        if (x->key > value)
            x = x->left;
        else
            x = x->right;
    }
    return NULL;
}

void AVLTree::deleteNode(Node* x) {
    if (x == nullptr) return;
    Node *y;
    Node *z;

    if (x->left && x->right) {
        y = findMax(x->left);
        x->key = y->key;
        x = y;
    }
    z = x->parent;
    if (x->left)
        y = x->left;
    else
        y = x->right;

    if (z == NULL || z->left == x)
        leftJoin(z, y);
    else
        rightJoin(z, y);
    delete x;
    x = nullptr;
    while (z != nullptr) {
        balance(z);
        updateHeight(z);
        z = z->parent;
    }
}

void AVLTree::deleteKey(int value) {
    deleteNode(search(value));
}

void AVLTree::inOrder(Node* x) {
    if (x == nullptr) return;
    inOrder(x->left);
    cout << x->key << " ";
    inOrder(x->right);
}

void AVLTree::inOrder() {
    inOrder(this->root);
}

void AVLTree::postOrder(Node* x) {
    if (x == nullptr) return;
    postOrder(x->left);
    postOrder(x->right);
    cout << x << " ";
}

void AVLTree::postOrder() {
    postOrder(this->root);
}

void AVLTree::travel() {
    queue<pair<Node*, int>> Q;
    Q.push({root, 0});
    while (Q.size()) {
        Node* u = Q.front().first; 
        int depth = Q.front().second;
        Q.pop();
        if (u == nullptr) continue;
        cout << u->key << " " << u->height << " --- " << depth << endl;
        Q.push({u->left, depth + 1});
        Q.push({u->right, depth + 1});
    }

}
/*----------------------------------------------------------------- */

void task1() {
    freopen("input.txt", "r", stdin);
    AVLTree A;
    int x;
    while (cin >> x) {
        A.insertKey(x);
    }
    A.postOrder();
    
}

void runTask() {
    freopen("input.txt", "r", stdin);
    int x, m;
    AVLTree A;
    while (scanf("%d", &m) > 0) {
        //cout << m << endl;
        if (m == 1) {
            scanf("%d", &x);
            A.insertKey(x);
            A.travel();
        }
        if (m == 2) {
            scanf("%d", &x);
            A.deleteKey(x);
        }
        if (m == 3) {
            if (A.isEmpty())
                puts("empty");
            else
                printf("%d\n", A.findMin()->key);
        }
        if (m == 4) {
            if (A.isEmpty())
                puts("empty");
            else
                printf("%d\n", A.findMax()->key);
        }
        if (m == 5) {
            scanf("%d", &x);
            Node* f = A.successor(x);
            if (A.isEmpty())
                puts("empty");
            else if (f == NULL)
                puts("no");
            else
                printf("%d\n", f->key);
        }
        if (m == 6) {
            scanf("%d", &x);
            if (A.isEmpty())
                puts("empty");
            else {
                Node* f = A.search(x);
                if (f == NULL) 
                    f = A.successor(x);
                if (f == NULL)
                    puts("no");
                else
                    printf("%d\n", f->key);
            }
        }
        if (m == 7) {
            scanf("%d", &x);
            Node* f = A.predecessor(x);
            if (A.isEmpty())
                puts("empty");
            else if (f == NULL)
                puts("no");
            else
                printf("%d\n", f->key);
        }
        if (m == 8) {
            scanf("%d", &x);
            if (A.isEmpty())
                puts("empty");
            else {
                Node* f = A.search(x);
                if (f == NULL) 
                    f = A.predecessor(x);
                if (f == NULL)
                    puts("no");
                else
                    printf("%d\n", f->key);
            }
        }
    }
}

int main() {
    runTask();
    return 0;
    int a[] = {1, 7, 4, 9, 2, 6, 5, 4, 12, 13, 14};
    AVLTree A;
    for (int x : a) A.insertKey(x);
    A.travel();
    A.deleteKey(12);
    A.deleteKey(1);
    A.deleteKey(7);
    cout << endl;
    A.travel();
    return 0;
}