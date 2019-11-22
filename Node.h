#ifndef NODE_H
# define NODE_H
#include "clockcalendar.h"

#include <iostream>
using namespace std;
class entry{
public:
  ClockCalendar time;
  double price;
  string refri;
};

template <class T>
class Node {


    T val;
    Node* next;
    Node* prev;

  public:

    Node(T dat, Node* nxt, Node* prv);
    T getVal();
    Node* getNext();
    Node* getPrev();
    void setVal(T dat);
    void setNext(Node<T>* nxt);
    void setPrev(Node<T>* prv);
};

#endif
