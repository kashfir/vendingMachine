#ifndef INTERFACEPC
#define INTERFACEPC

#include <time.h>
#include<limits>
#include <thread>
#include <sstream>
#include "Maquina.h"
#include "List.h"




class InterfacePC : public Maquina {
		// entry registro;
		ClockCalendar systemClock;
		List<entry> log;
public:

	InterfacePC(void);
	~InterfacePC(void);
	void sendCommand(char cmd);
	void printMenu();
	void inputCommand();
	void timeCount();
};


#endif // INTERFACEPC
