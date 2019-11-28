#ifndef INTERFACEPC_H
#define INTERFACEPC_H

#include <time.h>
#include <thread>
#include <mutex>
#include <limits>
#include "Maquina.h"
#include "Log.h"
#include "Vector.h"



class InterfacePC : public Maquina {
		// entry registro;
		ClockCalendar systemClock;
		Log logPC;
		Vector admins;
		char cmd,state, oldState;
		std::mutex mtx;
		List<task_t> taskList;
		List<task_t> readyTaskList;

		// void (*foo)(void);
public:

	InterfacePC(void);
	~InterfacePC(void);
	void setSystemTime();
	void sendCommand(char cmd);
	void printMenu();
	void inputCommand();

	void timeCount();

	void updateSM();
	void updateDisplay();
	void updateInput();

	void adminLogin();
	void adminMenu(std::string user);

	void tick_timer_intr(void);
	void ISR();
	void roundRobin(void);
	void roundRobinInterrupt(void);
	int addTask(void (*task)(void), int time);
	void removeTask(std::function<void (void)>);
};


#endif // INTERFACEPC
