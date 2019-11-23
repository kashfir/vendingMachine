#include "clock.h"
#include "calendar.h"
#include "ClockCalendar.h"
#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

void ClockCalendar::advance (){
  int was_pm=is_pm;
  Clock::advance();
  if ((was_pm==1) & (is_pm==0)){
    Calendar::advance();
  }
}

void operator++ (ClockCalendar& t){
int was_pm=t.is_pm;
    t.Clock::advance();
    if ((was_pm==1) & (t.is_pm==0)){
      t.Calendar::advance();
    }
}

std::ostream& operator<< (std::ostream& c, ClockCalendar t){
 int hr, min, sec, pm, m, d, y;
  t.readClock(hr,min,sec,pm);
	t.readCalendar(m,d,y);
  c << std::setfill('0') << std::setw(2) << hr
  <<":"<< std::setfill('0') << std::setw(2) << min
   <<":" << std::setfill('0') << std::setw(2) << sec << (pm?"PM":"AM")
   << " "<< std::setfill('0') << std::setw(2) << d
   << "/" << std::setfill('0') << std::setw(2) << m
   << "/" << std::setfill('0') << std::setw(2) << y;
	return c;

}
