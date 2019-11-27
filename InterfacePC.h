#ifndef INTERFACEPC
#define INTERFACEPC

#include <time.h>
// #include<limits>
#include <thread>
#include <sstream>
#include <ctime>
#include "Maquina.h"
#include "Log.h"
#include "Vector.h"




class InterfacePC : public Maquina {
		// entry registro;
		ClockCalendar systemClock;
		Log logPC;
		Vector admins;
		char cmd;
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
};


#endif // INTERFACEPC
