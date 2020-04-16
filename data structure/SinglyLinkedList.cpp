/**************************************
    data-structure: singly linked list 
    author: jugthanh                    
    created: 19.03.2020
***************************************/

#include <iostream>
#include <list>

using namespace std;

template<typename T>
struct Node {
    T key;
    Node* next;
    Node(T _key = 0, Node* _next = NULL): key(_key), next(_next) {}
};

template<typename T>
class CLinkedList { //1-base-index
private:
    Node<T> *head, *tail;
public:
    CLinkedList() {head = tail = NULL;};
    CLinkedList(const CLinkedList&);
    ~CLinkedList();

    bool isEmpty();
    void push_back(T);   // append new node to tail of list
    void push_front(T);  // insert new node to head of list
    void insert(int, T); // insert at a specific position 
    void pop_back();     // remove a node at beginning
    void pop_front();    // remove a node at the end
    void remove(int);    // remove at specific position
    void display();      // print all element in list   

    void reverse(); 
    void sort();
};

/// -------------- implement member function------------------\\\

template<typename T>
CLinkedList<T>::CLinkedList(const CLinkedList<T>& other) { 
    head = NULL;
    Node<T>* temp = other.head;
    while (temp) {
        this->push_back(temp->key);
        temp = temp->next;
    }
}

template<typename T>
CLinkedList<T>::~CLinkedList() { 
    while (head) { //no need
        Node<T> *tmp = head;
        head = head->next;
        delete tmp;
        tmp = NULL;
    }
    head = tail = NULL;
}

template<typename T>
bool CLinkedList<T>::isEmpty() {
    return head == NULL;
}

/// ------> insert element <------

template<typename T>
void CLinkedList<T>::push_back(T value) {
    Node<T> *newNode = new Node<T>(value);
    if (head == NULL) head = tail = newNode;
    else tail->next = newNode, tail = newNode;
}

template<typename T>
void CLinkedList<T>::push_front(T value) {
    Node<T> *newNode = new Node<T>(value, head);
    if (tail == NULL) tail = head;
    head = newNode;
}

template<typename T>
void CLinkedList<T>::insert(int position, T value) {
    Node<T> *ptr = head;
    if (position-- == 1) {
        push_front(value);
        return;
    }
    while (ptr != NULL) {
        if (--position == 0) {
            Node<T> *newNode = new Node<T>(value, ptr->next);
            if (ptr == tail) tail = newNode;
            ptr->next = newNode;
            break;
        }
        ptr = ptr->next;
    }
    if (position) throw "Error: Insert position out of range";
}

/// ------> remove element <------

template<typename T>
void CLinkedList<T>::pop_back() {
    if (head == NULL) throw "Error: Nothing to remove";
    if (head->next == NULL) {
        head = tail = NULL;
        return;
    }
    Node<T> *temp = head, *prev;
    while (temp->next) prev = temp, temp = temp->next;
    prev->next = NULL;
    tail = prev;
    delete temp;
}

template<typename T>
void CLinkedList<T>::pop_front() {
    if (head == NULL) throw "Error: Nothing to remove";
    Node<T> *temp = head;
    head = head->next;
    delete temp;
    if (!head) tail = NULL;
}

template<typename T>
void CLinkedList<T>::remove(int position) {
    Node<T>* prev;
    Node<T>* ptr = head;
    if (position == 1) {
        pop_front();
        return;
    }
    while (ptr != NULL) {
        if (--position == 0) {
           prev->next = ptr->next;
           if (ptr == tail) tail = prev;
           delete ptr;
           break;
        }
        prev = ptr;
        ptr = ptr->next;
    }
    if (position) throw "Error: Remove position out of range";
}

template<typename T>
void CLinkedList<T>::display() {
    int cnt = 0;
    for (Node<T> *it = head; it != NULL; it = it->next) {
        cout << (it->key) << " ";
       // if (++cnt == 30) break;
    }
    cout << endl;
}

// -----> some function for fun :p <-----

template<typename T>
void CLinkedList<T>::reverse() {
    Node<T> *ptr = head;
    Node<T> *hrev = NULL, *trev = NULL;
    while (ptr) {
        Node<T>* temp = ptr->next;
        ptr->next = hrev;
        if (!trev) trev = ptr;
        hrev = ptr;
        ptr = temp;
    }
    head = hrev; tail = trev;
}

template<typename T>
void CLinkedList<T>::sort() { //bubble sort
    bool swapped = true;
    while (swapped) {
        swapped = false;
        Node<T>* y = head, *pre = NULL;
        while (y->next != NULL) {
            if (y->key > y->next->key) {
                Node<T> *temp = y->next;
                y->next = y->next->next;
                temp->next = y;
                if (y == head) head = temp;
                else pre->next = temp;
                swap(y, temp);
                swapped = true;
            }
            pre = y;
            y = y->next;
        } 
        tail = y;
    }
}

int main() {
    CLinkedList<int> A;
    
    try {
        for (int i = 1; i <= 5; i++) 
            A.push_back(i);
        A.insert(2, 12);
        //A.insert(4, 15);
        //A.insert(8, 100);
        A.push_back(214);
        A.display();
        A.remove(1);
        A.display();
        A.pop_front();
        A.display();
     
        A.display();
        A.push_front(123);
        A.push_back(1121);
        /*
        A.pop_back();
        A.remove(1);
        A.pop_back();
        A.remove(1);
        A.pop_front();
        A.remove(2);
        A.pop_back();
        A.remove(1);
        A.pop_back();
        */
       
        A.display();
        A.reverse();
        A.display();
        A.push_back(7);
        A.push_front(7);
        
        A.display();
        A.sort();
        A.display();
        A.push_back(7777);
        A.display();
        
    } catch (const char* msg) {
        cerr << msg << endl;
    }
    
    
    CLinkedList<int> B;
    B.push_back(8);
    B.push_back(5);
    B.push_back(2);
    B.push_back(3);
    B.push_back(1);
    B.sort();
    A.display();
    B.display();
    return 0;
}
