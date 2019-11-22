
#include "Node.h"

template <class T> Node<T>::Node(T dat,Node* nxt, Node* prv){
  val = dat;
  next = nxt;
  prev = prv;
}

template <class T> T Node<T>::getVal(){return val;}

template <class T> Node<T>* Node<T>::getNext(){return next;}

template <class T> Node<T>* Node<T>::getPrev(){return prev;}

template <class T> void Node<T>::setVal(T dat){
  val = dat;
}

template <class T> void Node<T>::setNext(Node* nxt){
  next = nxt;
}

template <class T> void Node<T>::setPrev(Node* prv){
  prev = prv;
}

template class Node<string>;
