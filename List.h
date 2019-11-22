#ifndef LIST_H
# define LIST_H

#include "Node.h"

// class entry{
// public:
//   string time;
//   double price;
//   string refri;
// };

template <class T>
class List {
  Node<T>* head;
public:
  List();
  ~List();
  // void insertBeforeFirst(T dat);
  void insertAfterLast(T dat);
  //
  T readFirst();
  // T readNode(Node<T>* a);
  int removeFirst();
  //
  // //
  // void insertionSort(T value);
  // T removeNode(T dat);
  // // //
  // void listAll();
  // void listAssociated();
  // // //
  // T readPrevious(Node<T>* dat);
  // T readPrevious(T dat);
  // T readNext(Node<T>* dat);
  // T readNext(T dat);
  // // //
  // // //
  // Node<T>* returnNode(T dat);
  // Node<T>* returnLast();


};

#endif
