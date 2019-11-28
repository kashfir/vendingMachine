#include <iostream>
#include "InterfacePC.h"

#define NSEC_PER_SEC 1000000000L

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
  oldState = S000;
  setSystemTime();
  printMenu();
  std::thread isr(&InterfacePC::ISR,this);
  isr.detach();
  std::thread rr(&InterfacePC::roundRobinInterrupt,this);
  rr.detach();
  std::thread input(&InterfacePC::updateInput,this);
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
  std::cin >> entrada;
   try{
      if(std::cin.fail()){
          throw "Erro! Insira uma das opcoes numericas do menu.";
      }
      if(entrada<1 || entrada>9){
          std::cout << "**Opcao nao disponivel!" << '\n';
      }
  }
  catch(const char* error){
     std::cout<<error<<std::endl;
     std::cin.clear(); // Clear error flags
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear out the input buffer
    return;
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
   ++systemClock;
}
void InterfacePC::updateSM(){
    state = nextState(cmd);
    if (state != oldState) {printMenu();}
    oldState = state;
    cmd = 1;
}
void InterfacePC::updateDisplay(){
  printMenu();
}
void InterfacePC::updateInput(){
  struct timespec t;
  clock_gettime(CLOCK_MONOTONIC ,&t);
   while(1)
   {
     clock_nanosleep(CLOCK_MONOTONIC, TIMER_ABSTIME, &t, NULL);

    inputCommand();//

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
    std::cin >> user;
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
  std::cin >> user;
  if (admins.userExists(user)){
    std::cout << "Digite a senha:" << '\n';
    std::cin >> pass;
    if(admins.login(user,pass)) {
      adminMenu(user);
    }

  }
  else {std::cout << "\n**Usuario nao existente." << '\n';}
}

void InterfacePC::adminMenu(std::string user){
  int entrada, logged, i;
  std::string pass, newUser,newPass, newVerify, usr2delete;
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
    std::cout << "7 - Despejo do log." << '\n';
    std::cout << "8 - Sair" << "\n\n\n";
    // try{
      std::cin >> entrada;
    //   if (entrada<1 || entrada>8){
    //     throw entrada;
    //   }
    // }
    // catch (int entrada){
    //   // cout << string( 20, '\n' );
    //   std::cout << "**Opcao nao disponivel!" << '\n' << '\n';
    //   // std::cout << "Pressione ENTER para continuar." << '\n';
    //   std::cin.ignore();
    // }
    switch (entrada) {
      case 1:{
        std::cout << "Digite um nome de usuario:" << '\n';
        std::cin >> newUser;
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
        std::cin >> usr2delete;
        if (!(usr2delete==user)) admins.removeAdmin(usr2delete);
        else std::cout << "**Nao e possivel remover voce mesmo." << '\n';
      } break;

      case 3:{
        std::cout << "**Digite a senha atual:" << '\n';
        std::cin >> pass;
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
      case 7:{ logPC.dump();} break;
      case 8:{ logged = 0;} break;
      }
    }
}

void InterfacePC::tick_timer_intr(void){
  List<task_t> bufferList;
  task_t bufferTask;
  while(taskList.readFirst(bufferTask)){
    if ((bufferTask.enabled == 1) && (bufferTask.elapsed != 0)){
      bufferTask.elapsed--;
    }
    if (bufferTask.elapsed <= 0){// se estiver pronta,
      bufferTask.elapsed = bufferTask.period;
      // std::cout << "tarefa " << bufferTask.task << " pronta!" << '\n';
      // bufferTask.task();

      readyTaskList.insertAfterLast(bufferTask); // vai para a lista de tarefas prontas para executar
    }
    else{ // se nao
      bufferList.insertAfterLast(bufferTask); // vai para o buffer para retornar a lista de tarefas esperando
    }
    taskList.removeFirst();
  }
  while(bufferList.readFirst(bufferTask)){
    taskList.insertAfterLast(bufferTask);
    bufferList.removeFirst();
  }
}

void InterfacePC::ISR(){
  struct timespec t;
  clock_gettime(CLOCK_MONOTONIC ,&t);
   while(1)
   {
     clock_nanosleep(CLOCK_MONOTONIC, TIMER_ABSTIME, &t, NULL);
     mtx.lock();
     tick_timer_intr();
     mtx.unlock();
     t.tv_nsec += 1000000L; //1ms
       if (t.tv_nsec>(NSEC_PER_SEC-1)) { // avoid overflow
         t.tv_sec+= 1;
         t.tv_nsec-=NSEC_PER_SEC;
       }
    }
}

void InterfacePC::roundRobin(void){
  task_t taskToRun;
    if (readyTaskList.readFirst(taskToRun)){
    std::thread t1(taskToRun.task);
    t1.detach();
    readyTaskList.removeFirst();
    taskList.insertAfterLast(taskToRun);    // if preempted, should re-insertafterLast in readyTaskList
  }
}

void InterfacePC::roundRobinInterrupt(void){
  struct timespec t;
  clock_gettime(CLOCK_MONOTONIC ,&t);
   while(1)
   {
     clock_nanosleep(CLOCK_MONOTONIC, TIMER_ABSTIME, &t, NULL);
     roundRobin();
     t.tv_nsec += 20000000L; //20ms   // quantum
       if (t.tv_nsec>(NSEC_PER_SEC-1)) { // avoid overflow
         t.tv_sec+= 1;
         t.tv_nsec-=NSEC_PER_SEC;
       }
    }
}

int InterfacePC::addTask(void (*task)(void), int time){
  task_t newTask;
  newTask.task = task;
  newTask.task();
  newTask.elapsed = time;
  newTask.period = time;
  newTask.enabled = 1;
  taskList.insertAfterLast(newTask);
  return 1;
}

void InterfacePC::removeTask(std::function<void (void)> task){
  typedef void function_t (void);
  function_t* ptr_task = task.target<function_t>();
  List<task_t> bufferList;
  task_t bufferTask;
  while(taskList.readFirst(bufferTask)){
    if (bufferTask.task != ptr_task){
      bufferList.insertAfterLast(bufferTask);
    }
    taskList.removeFirst();
  }
  while(bufferList.readFirst(bufferTask)){
  taskList.insertAfterLast(bufferTask);
  bufferList.removeFirst();
  }
}
