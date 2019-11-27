#ifndef NODE_H
# define NODE_H
#include "ClockCalendar.h"
#include <iostream>


class entry{
public:
  ClockCalendar time;
  double price;
  std::string refri;
};

typedef struct {
  int period;
  int elapsed;
  int enabled;
  void (*task)(void);
} task_t;

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
