#include <iostream>
#include "InterfacePC.h"
#define NSEC_PER_SEC 1000000000L
using namespace std;


#define S000	0x1
#define S025	0x2
#define S050	0x4
#define S075	0x8
#define S100	0x10
#define S125	0x20
#define S150	0x40

#define D025 0x1
#define D050 0x2
#define D100 0x4
#define LMEET 0x8
#define LETIRPS 0x10
#define INSUFF 0x20

#define Nada 0x1
#define M025 0x2
#define M050 0x4
#define M100 0x8
#define DEV 0x10
#define MEET	0x20
#define ETIRPS	0x40

InterfacePC::InterfacePC(void){
  thread t(&InterfacePC::timeCount,this);
  t.detach();
}

InterfacePC::~InterfacePC(void){

}

void InterfacePC::sendCommand(char cmd){
    ostringstream stream; // <sstream> lib

    if (D025 & cmd) std::cout << "Devolveu R$ 0,25!" << '\n';
    if (D050 & cmd) std::cout << "Devolveu R$ 0,50!" << '\n';
    if (D100 & cmd) std::cout << "Devolveu R$ 1,00!" << '\n';
    if (LMEET & cmd){
      stream << systemClock;
      log.insertAfterLast(stream.str() + "\t" + "MEET"+ "\t" + "1,50");
      log.listAll();
      std::cout << "Saindo um Meet!" << '\n';
      }
    if (LETIRPS & cmd){
      stream << systemClock;
      log.insertAfterLast(stream.str() + "\t" + "ETIRPS"+ "\t" + "1,50");
      log.listAll();
      std::cout << "Saindo um Etirps!" << '\n';
      }
    if (INSUFF & cmd) std::cout << "Saldo insuficiente!" << '\n';
    std::cout << '\n';
}

void InterfacePC::printMenu(){
  char saldo = getState();
  std::cout << "1 - Inserir R$ 0,25." << '\n';
  std::cout << "2 - Inserir R$ 0,50." << '\n';
  std::cout << "3 - Inserir R$ 1,00." << '\n';
  std::cout << "4 - Pedir Devolução." << '\n';
  std::cout << "5 - Requisitar um Meet." << '\n';
  std::cout << "6 - Requisitar um Etirps." << '\n' << '\n';
  std::cout << "Saldo atual: R$ ";
  switch (saldo) {
    case S000: std::cout << "0,00"; break;
    case S025: std::cout << "0,25"; break;
    case S050: std::cout << "0,50"; break;
    case S075: std::cout << "0,75"; break;
    case S100: std::cout << "1,00"; break;
    case S125: std::cout << "1,25"; break;
    case S150: std::cout << "1,50"; break;
  }
  std::cout <<'\n';
}

void InterfacePC::inputCommand(){
  int entrada;
  char cmd = 1;
  std::cin >> entrada;
  if (cin.fail()){
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(),'\n');
    cout<<"Comando nao encontrado!"<<endl;
    return ;
  }
  if (cin.good()){
  if (entrada == 7){
    std::cout << "Menu de servico:" << '\n' << '\n';
    std::cout << "Em construcao..." << '\n' << '\n';
  } else if (entrada>0 && entrada <7){
  std::cout << '\n' << '\n';
  cmd <<= entrada;
  nextState(cmd);
  }
  else {
    std::cout << "Comando nao encontrado!" << '\n';
  }
  }
}

void InterfacePC::timeCount(){
  struct timespec t;
  clock_gettime(CLOCK_MONOTONIC ,&t);
   while(1)
   {
     clock_nanosleep(CLOCK_MONOTONIC, TIMER_ABSTIME, &t, NULL);
     ++systemClock;
     t.tv_sec++;
    }
}
