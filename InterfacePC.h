#ifndef INTERFACEPC
#define INTERFACEPC

#include <time.h>
#include<limits>
#include <thread>
#include <sstream>
#include "Maquina.h"
#include "clockcalendar.h"
#include "List.h"




class InterfacePC : public Maquina {
		ClockCalendar systemClock;
		List<string> log;
public:

	InterfacePC(void);
	~InterfacePC(void);
	void sendCommand(char cmd);
	void printMenu();
	void inputCommand();
	void timeCount();
};


#endif // INTERFACEPC
