#include "List.h"

template <class T> List<T>::List(){
     head = 0;
}

template <class T> List<T>::~List(){
  Node<T>* cursor = head;
  while(head) {
    cursor = cursor->getNext();
    delete head;
    head = cursor;
  }
  head = 0; // Officially empty
}

template <class T> void List<T>::insertBeforeFirst(T dat){
  Node<T>* p = head;
  if (head == 0)
     head = new Node<T>(dat, head,0);
  else{
  head = new Node<T>(dat,head,0);
  p->setPrev(head);
  }
}
//
template <class T>  void List<T>::insertAfterLast(T dat){
  Node<T>* p = head;
  Node<T>* q = head;

  if (head == 0)      //Se a lista estiver vazia
     head = new Node<T>(dat, head,0); //cria o primeiro nodo
  else {              //Se a lista nao estiver vazia
     while (q != 0) { //Enquanto o ponteiro auxiliar 'q' for diferente de zero
        p = q;  //'p' recebe 'p' antes de incrementar o nodo
        q = p->getNext(); // 'q' recebe o proximo nodo
     }
     p->setNext(new Node<T>(dat,0,p)); //cria-se o nodo em 'p' que aponta para NULL
  }
}
//
template <class T> T List<T>::readFirst(){
  return head->getVal();
}
//
template <class T> T List<T>::readNode(Node<T>* a){
    return (a->getVal());
  }

template <class T> T List<T>::removeFirst(){
  T oldVal = 0;
  if (head != 0){
    oldVal = head->getVal();
    Node<T>* oldHead = head;
    head = head->getNext();
    head->setPrev(0);
    delete oldHead;
  }
  return oldVal;
}

template <> string List<string>::removeFirst(){
  string oldVal = "";
  if (head != 0){
    oldVal = head->getVal();
    Node<string>* oldHead = head;
    head = head->getNext();
    head->setPrev(0);
    delete oldHead;
  }
  return oldVal;
}

//
template <class T>  void List<T>::insertionSort(T value){
  Node<T>* p = head;
  Node<T>* q = head;

  if (head==0){
    head = new Node<T>(value,head,0);
  }
  else  {
	  T pint;
	  T auxint;
	  pint = q->getVal(); // 'pint' recebe o valor do em 'q'
	  auxint = pint; // 'auxint' recebe 'pint'
	  while ((q != 0) && (auxint < value)) //Enquanto 'q' não apontar para null & se o valor do item a ser inserido for maior que o valor em 'auxint'
	  {
		  p = q; // Salva o auxiliar em 'p'
		  q = p->getNext();//Incrementa o nodo auxiliar 'q'
		  if (q != 0) // Se o proximo nao for o ultimo nodo
		  {
			pint = q->getVal(); //toma o valor do ultimo
			auxint = pint; // e repassa ao auxiliar
		  }
	  }
	  if (p == q){ //caso o valor do primeiro nodo seja maior que o valor do nodo a adicionar
		  head = new Node<T>(value,head,0);
      q->setPrev(head); //Define o nodo adicionado como anterior ao a seguir
    }
	  else{
      p->setNext(new Node<T>(value,q,p)); // insere o novo nodo entre 'p' e 'q'
      if (q != 0)
      q->setPrev(p->getNext());//Define o nodo adicionado como anterior ao a seguir
    }
  }
}
//
template <class T> T List<T>::removeNode(T dat){
  Node<T>* p = head;
  Node<T>* q = head;
  T result;

  if (head == 0) //feriadinho, ta vazio
     result = 0;
  else {
	  while ((q != 0) && (q->getVal() != dat)){  // Error!! the addresses will always be different!
		  p = q;
		  q = p->getNext();
	  }

	  if (q != 0) {
		  if (q == head){	// it is the first node
			  result = q->getVal();
			  head = q->getNext();
        head->setPrev(0);
			  delete q;
		  }
		  else if (q->getNext() == 0){ // it is the last node
        result = q->getVal();
        std::cout << "q->getNext() == 0" << '\n';
        p->setNext(0);
        delete q;
      }
      else{				// the node is in the middle
			  result = q->getVal();
			  p->setNext(q->getNext());
        (q->getNext())->setPrev(p);
			  delete q;
		  }
	  }
	  else
		  result = 0;		// node not found!
  }

  return result;
}
template <> string List<string>::removeNode(string dat){
  Node<string>* p = head;
  Node<string>* q = head;
  string result;

  if (head == 0) //feriadinho, ta vazio
     result = "";
  else {
	  while ((q != 0) && (q->getVal() != dat)){  // Error!! the addresses will always be different!
		  p = q;
		  q = p->getNext();
	  }

	  if (q != 0) {
		  if (q == head){	// it is the first node
			  result = q->getVal();
			  head = q->getNext();
        head->setPrev(0);
			  delete q;
		  }
		  else if (q->getNext() == 0){ // it is the last node
        result = q->getVal();
        p->setNext(0);
        delete q;
      }
      else{				// the node is in the middle
			  result = q->getVal();
			  p->setNext(q->getNext());
        (q->getNext())->setPrev(p);
			  delete q;
		  }
	  }
	  else
		  result = "not found";		// node not found!
  }

  return result;
}
//
template <class T> void List<T>::listAll(){
  Node<T>* aux = head;
  while (aux != 0){
     cout << aux->getVal() << '\n';
     aux = aux->getNext();
  }
  cout << endl;
}
template <class T> void List<T>::listAssociated(){
  Node<T>* aux = head;
  while (aux != 0){
     cout << "("<< readPrevious(aux) << "," << readNext(aux) << ")" << '\t';
     aux = aux->getNext();
  }
  cout << endl;
}
template <class T> T List<T>::readPrevious(Node<T>* a){
  if ((a == 0) ||(a->getPrev()==0))  return 0;
  return (a->getPrev()->getVal());
}
template <> string List<string>::readPrevious(Node<string>* a){
  if ((a == 0) ||(a->getPrev()==0))  return "0";
  return (a->getPrev()->getVal());
}
template <class T> T List<T>::readPrevious(T dat){
  Node<T>* p = head;
  if (p == 0) return 0;

  while ((p->getVal() != dat)){
    p = p->getNext();
    if (p == 0){
      return 0;
    }
  }
  return (p->getPrev()->getVal());
}
template <> string List<string>::readPrevious(string dat){
  Node<string>* p = head;
  if (p == 0) return "0";

  while ((p->getVal() != dat)){
    p = p->getNext();
    if (p == 0){
      return "0";
    }
  }
  return (p->getPrev()->getVal());
}
template <class T> T List<T>::readNext(T dat){
  Node<T>* p = head;
  while ((p->getVal() != dat)){
    p = p->getNext();
    if (p = 0){
      return 0;
    }
  }
  return p->getNext()->getVal();
}
template <> string List<string>::readNext(string dat){
  Node<string>* p = head;
  while ((p->getVal() != dat)){
    p = p->getNext();
    if (p == 0){
      return "0";
    }
  }
  return p->getNext()->getVal();
}
template <class T> T List<T>::readNext(Node<T>* a){
  if ((a == 0) ||(a->getNext()==0))   return 0;
  return a->getNext()->getVal();
}
template <> string List<string>::readNext(Node<string>* a){
  if ((a == 0) ||(a->getNext()==0))   return "0";
  return a->getNext()->getVal();
}
// //
template <class T> Node<T>* List<T>::returnNode(T dat){
  Node<T>* p = head;
  while ((p->getVal() != dat)){
    p = p->getNext();
  }
  return p;
}
template <class T> Node<T>* List<T>::returnLast(){
  Node<T>* p = head;
  Node<T>* q = head;
  while (q != 0){
    p=q;
    q = p->getNext();
  }
  return p;
}


template class List<string>; //So the compiler knows that it should create a String type List class
