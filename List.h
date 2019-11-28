/*
Arquivo: List.h
Autor: Thiago Daros Fernandes
Data: 15/11/2019
Descricao: Este arquivo e responsavel por declarar a classe List que forma a
lista duplamente encadeada.
A lista pode assumir nodos que guardam diferentes tipos de dados, tal como uma
estrutura. Esta lista funciona como pilha invertida, FIFO. So e possivel adicionar
elementos no final da pilha, e so e possivel ler o elemento do inicio.
*/


#ifndef LIST_H
#define LIST_H
#include "Node.h"



/*
Classe: List
Descricao: Possui como objeto um ponteiro para o primeiro nodo da lista. Esta
 lista funciona como pilha invertida, FIFO. So e possivel adicionar
elementos no final da pilha, e so e possivel ler o elemento do inicio.
*/
template <class T>
class List {
  Node<T>* head;
public:
  List();
  ~List();
  void insertAfterLast(T dat);
  bool readFirst(T&); // se vazio retorna 0, se nao 1
  bool removeFirst();  // se vazio retorna 0, se nao 1
};

#endif
