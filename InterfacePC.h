/*
Arquivo: InterfacePC.h
Autor: Thiago Daros Fernandes
Data: 27/10/2019
Descricao: Este arquivo e responsavel por declarar a classe InterfacePC que
reune as funcionalidades da maquina para operar em um PC. As funcoes de I/O do
PC e outras bibliotecas exclusivas para um sistema com SO foram reunidas nessa
 secao do codigo para que ele seja compilavel em mais de uma plataforma. O
 escalonar esta incluso nesta classe.
*/

#ifndef INTERFACEPC_H
#define INTERFACEPC_H

#include <time.h>
#include <thread>
#include <mutex>
#include <limits>
#include "Maquina.h"
#include "Log.h"
#include "Vector.h"


/*
Classe: InterfacePC
Descricao:
- Herda a classe Maquina para funcionar como interface. Define a funcao
abstrata de Maquina "sendCommand".
- Possui um objeto ClockCalendar "systemClock" que guarda a hora do sistema e eh
utilizado como referencia para escrita no log.
- Objeto Log "logPC" que eh o log do sistema.
- Objeto Vector "admins" que guarda os admins cadastrados
- Possui listas de tarefas periodicas para serem executadas e uma lista de
tarefas prontas para executarem, do tipo List.
*/
class InterfacePC : public Maquina {
		// entry registro;
		ClockCalendar systemClock;
		Log logPC;
		Vector admins;
		char cmd,state, oldState;
		std::mutex mtx;
		List<task_t> taskList;
		List<task_t> readyTaskList;
public:
	InterfacePC(void);
	~InterfacePC(void);

// SM
	void sendCommand(char cmd);
	void printMenu();
	void inputCommand();
// CLOCK
	void timeCount();
	void setSystemTime();
// TASKS
	void updateSM();
	// void updateDisplay(); task necessaria apenas para a plataforma embarcada.
	void updateInput();
// ADMINS
	void adminLogin();
	void adminMenu(std::string user);
// SCHEDULER
	void tick_timer_intr(void);
	void ISR();
	void roundRobin(void);
	void roundRobinInterrupt(void);
	int addTask(void (*task)(void), int time);
	void removeTask(void (*task)(void));
};


#endif // INTERFACEPC
