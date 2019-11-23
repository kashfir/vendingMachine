#ifndef CLOCKCALENDAR_H
# define CLOCKCALENDAR_H
#include "clock.h"
#include "calendar.h"
#include <iostream>
#include <string>


class ClockCalendar : public Clock, public Calendar {
 public:
    ClockCalendar () : Clock (0, 0, 0, 0), Calendar (0, 0, 0){};
  	ClockCalendar (int mt, int d, int y, int h, int m, int s, int pm) : Clock (h, m, s, pm), Calendar (mt, d, y){};
  	void advance();
	friend void operator++ (ClockCalendar& t);
	friend std::ostream& operator<< (std::ostream&, ClockCalendar);
};




#endif
