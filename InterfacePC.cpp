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
  cmd = 1;
  thread clock(&InterfacePC::timeCount,this);
  clock.detach();
  thread stateMachine(&InterfacePC::updateSM,this);
  stateMachine.detach();
  // thread display(&InterfacePC::updateDisplay,this);
  // display.detach();
  thread input(&InterfacePC::updateInput,this);
  input.detach();
}

InterfacePC::~InterfacePC(void){

}

void InterfacePC::setSystemTime(){ // WORKING ON LINUX
  time_t tt;
  int pm, hr;
  time (&tt);
  struct tm * ti = localtime(&tt);
  if (ti->tm_hour>12){
    pm = 1;
    hr = ti->tm_hour-12;
  }
  else
  {
    pm=0;
    hr = ti->tm_hour;
  }
  systemClock.setClock (hr,ti->tm_min,ti->tm_sec,pm);
  systemClock.setCalendar(ti->tm_mon,ti->tm_mday,ti->tm_year+1900);
}

void InterfacePC::sendCommand(char output){
    if (D025 & output) std::cout << "-Devolveu R$ 0,25!" << '\n';
    if (D050 & output) std::cout << "-Devolveu R$ 0,50!" << '\n';
    if (D100 & output) std::cout << "-Devolveu R$ 1,00!" << '\n';
    if (LMEET & output){
      logPC.record(systemClock,1.50,"MEET");
      std::cout << "-Saindo um Meet!" << '\n';
      }
    if (LETIRPS & output){
      logPC.record(systemClock,1.50,"ETIRPS");
      std::cout << "-Saindo um Etirps!" << '\n';
      }
    if (INSUFF & output) std::cout << "**Saldo insuficiente!" << '\n';
}

void InterfacePC::printMenu(){
  char saldo = getState();
  std::cout << "1 - Inserir R$ 0,25." << '\n';
  std::cout << "2 - Inserir R$ 0,50." << '\n';
  std::cout << "3 - Inserir R$ 1,00." << '\n';
  std::cout << "4 - Pedir Devolução." << '\n';
  std::cout << "5 - Requisitar um Meet." << '\n';
  std::cout << "6 - Requisitar um Etirps." << '\n';
  std::cout << "7 - Login do administrador" << '\n';
  std::cout << "**Saldo atual: R$ ";
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
  try{
    std::cin >> entrada;
    if (entrada<1 || entrada>9){
      throw entrada;
    }
  }
  catch (int entrada){
    std::cout << "**Opcao nao disponivel!" << '\n';
  }
  if (entrada==7){
    adminLogin();
    printMenu();
  }
  else {
    cmd <<= entrada;
  }
}


void InterfacePC::timeCount(){
  struct timespec t;
  clock_gettime(CLOCK_MONOTONIC ,&t);
  setSystemTime();
   while(1)
   {
     clock_nanosleep(CLOCK_MONOTONIC, TIMER_ABSTIME, &t, NULL);
     ++systemClock;
     t.tv_sec++;
    }
}

void InterfacePC::updateSM(){
  char state, oldState;
  oldState = S000;
  struct timespec t;
  clock_gettime(CLOCK_MONOTONIC ,&t);
  setSystemTime();
  printMenu();
  while(1)
  {
    clock_nanosleep(CLOCK_MONOTONIC, TIMER_ABSTIME, &t, NULL);
    state = nextState(cmd);
    if (state != oldState) {printMenu();}
    oldState = state;
    cmd = 1;
    t.tv_nsec += 20000000L; //20ms
    if (t.tv_nsec>(NSEC_PER_SEC-1)) { // avoid overflow
      t.tv_sec+= 1;
      t.tv_nsec-=NSEC_PER_SEC;
    }
  }
}

void InterfacePC::updateDisplay(){
  struct timespec t;
  clock_gettime(CLOCK_MONOTONIC ,&t);
  setSystemTime();
  while(1)
  {
    clock_nanosleep(CLOCK_MONOTONIC, TIMER_ABSTIME, &t, NULL);
    printMenu();
    t.tv_sec+= 1;
  }
}

void InterfacePC::updateInput(){
  struct timespec t;
  clock_gettime(CLOCK_MONOTONIC ,&t);
  setSystemTime();
  while(1)
  {
    clock_nanosleep(CLOCK_MONOTONIC, TIMER_ABSTIME, &t, NULL);
    inputCommand();
    t.tv_nsec += 10000000L; //10ms
    if (t.tv_nsec>(NSEC_PER_SEC-1)) { // avoid overflow
      t.tv_sec+= 1;
      t.tv_nsec-=NSEC_PER_SEC;
    }
  }
}

void InterfacePC::adminLogin(){
  std::string user, pass, newPass, newVerify;
  int i = 0;
  if (admins.countUsers()==0){
    std::cout << "\n**Nenhum administrador cadastrado." << '\n';
    std::cout << "Digite um nome de usuario:" << '\n';
    cin >> user;
    while(!i){
      std::cout << "Digite a nova senha: "; std::cin >> newPass;
      std::cout << "Digite a nova senha novamente: "; std::cin >> newVerify;
      if (newPass!=newVerify){
        std::cout << "\n**Senhas informadas diferem." << '\n';

      }
      else{i = 1;}
    }
    admins.includeAdmin(user,newPass);
    std::cout << "\n**Usuario "<< user <<" criado com sucesso!" << "\n";
  }
  std::cout << "**Por favor faça login." << '\n';
  std::cout << "Digite o usuario:" << '\n';
  cin >> user;
  if (admins.userExists(user)){
    std::cout << "Digite a senha:" << '\n';
    cin >> pass;
    if(admins.login(user,pass)) {
      adminMenu(user);
    }

  }
  else {std::cout << "\n**Usuario nao existente." << '\n';}
}

void InterfacePC::adminMenu(string user){
  int entrada, logged, i;
  string pass, newUser,newPass, newVerify, usr2delete;
  logged = 1;
  std::cout << "\n\n**Bem-vindo " << user << "!\n\n";
  while(logged){
    i = 0;
    std::cout << "1 - Adicionar administrador." << '\n';
    std::cout << "2 - Remover admnistrador." << '\n';
    std::cout << "3 - Trocar minha senha." << '\n';
    std::cout << "4 - Exibir relatorio de arrecadacao." << '\n';
    std::cout << "5 - Exibir relatorio de vendas por refrigerante." << '\n';
    std::cout << "6 - Exibir relatroio de vendas por periodo." << '\n';
    std::cout << "7 - Sair" << "\n\n\n";
    try{
      std::cin >> entrada;
      if (entrada<1 || entrada>7){
        throw entrada;
      }
    }
    catch (int entrada){
      // cout << string( 20, '\n' );
      std::cout << "**Opcao nao disponivel!" << '\n' << '\n';
      // std::cout << "Pressione ENTER para continuar." << '\n';
      cin.ignore();
    }
    switch (entrada) {
      case 1:{
        std::cout << "Digite um nome de usuario:" << '\n';
        cin >> newUser;
        while(i<3){
          std::cout << "Digite a nova senha: "; std::cin >> newPass;
          std::cout << "Digite a nova senha novamente: "; std::cin >> newVerify;
          if (newPass!=newVerify){
            std::cout << "Senhas informadas diferem." << '\n';
            i++;
          }
          else{
            admins.includeAdmin(newUser,newPass);
            std::cout << "**Usuario "<< newUser <<" criado com sucesso!" << "\n\n";
            i=3;
          }
        }
      } break;

      case 2:{

        std::cout << "**Digite o nome de usuario:" << '\n';
        cin >> usr2delete;
        if (!(usr2delete==user)) admins.removeAdmin(usr2delete);
        else std::cout << "**Nao e possivel remover voce mesmo." << '\n';
      } break;

      case 3:{
        std::cout << "**Digite a senha atual:" << '\n';
        cin >> pass;
        if (admins.login(user,pass)) {
          while(i<3){
            std::cout << "**Digite a nova senha: "; std::cin >> newPass;
            std::cout << "**Digite a nova senha novamente: "; std::cin >> newVerify;
            if (newPass!=newVerify){
              std::cout << "**Senhas informadas diferem." << '\n';
              i++;
            }
            else{
              admins.changePassword(user,newPass);
              std::cout << "**Senha trocada com sucesso." << '\n';
              i=3;
            }
          }

        }

      } break;
      case 4:{
        std::cout << "\n\n\n**Total de vendas:\n";
        float vendas = logPC.getSales();
        int decimal = static_cast<int>(vendas*10)%10;
        std::cout << "R$ " << int(vendas) << "," << decimal << "0"<< "\n\n";
      } break;
      case 5:{
        int meet, etirps;
        std::cout << "\n\n\n**Total de vendas por refrigerante:";
        logPC.readSalesCount(meet,etirps);
        std::cout << "Meet: "<< meet << '\n';
        std::cout << "Etirps: "<< etirps << '\n';
      } break;
      case 6:{
        dayPeriod vendas;
        vendas = logPC.maxSalesPeriod();
        std::cout << "\n\n\n**Total de vendas por periodo:\n";
        std::cout << "Manhã: " << vendas.morning << '\n';
        std::cout << "Tarde: " << vendas.afternoon << '\n';
        std::cout << "Noite: " << vendas.evening << '\n';
        std::cout << "Madrugada: " << vendas.dawn << '\n';

      } break;
      case 7:{ logged = 0;} break;
      }
    }


}
