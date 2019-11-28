
/*
Arquivo: Node.h
Autor: Thiago Daros Fernandes
Data: 15/11/2019
Descricao: Este arquivo e responsavel por declarar a classe Node que formara a lista duplamente encadeada.
O nodo pode ter como valor um tipo de dado T definido pelo template, por isso pode ser utilizado em diferentes contextos.
*/

#ifndef NODE_H
# define NODE_H
#include "ClockCalendar.h"  //Bibli
#include <iostream>

/*
Classe: entry
Descricao: Estrutura que guarda informacoes sobre as entradas do log da maquina.
Possui um relogio, o preco do produto vendido e o nome do produto.
Pode ser alterada para guardar outras informacoes como codigo de barras, etc.
*/
class entry{
public:
  ClockCalendar time;
  double price;
  std::string refri;
};
/*
Struct: task_t
Descricao: Estrutura que guarda informacoes de cada tarefa do escalonador,
tal como o ponteiro para a funcao a ser executada, a periodicidade da tarefa
e o tempo restante para executar a tarefa novamente.
*/
typedef struct {
  int period;
  int elapsed;
  int enabled;
  void (*task)(void);
} task_t;

/*
Classe: Node
Descricao: Alem da variavel template, possui ponteiros para os Nodos adjacentes
para formar a lista encadeada.
Possui funcoes para definir e ler os objetos adjacentes e retornar seu dado
 guardado.
*/
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
