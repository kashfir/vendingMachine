#ifndef INTERFACEPC
#define INTERFACEPC

#include <time.h>
#include<limits>
#include <thread>
#include <sstream>
#include <ctime>
#include "Maquina.h"
#include "Log.h"




class InterfacePC : public Maquina {
		// entry registro;
		ClockCalendar systemClock;
		Log logPC;
public:

	InterfacePC(void);
	~InterfacePC(void);
	void setSystemTime();
	void sendCommand(char cmd);
	void printMenu();
	void inputCommand();
	void timeCount();
};


#endif // INTERFACEPC
