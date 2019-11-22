#include "clock.h"
#include "calendar.h"
#include "clockcalendar.h"
#include <iostream>
#include <string>
#include <iomanip>
#include <ctime>
using namespace std;

  void ClockCalendar::advance (){
    int was_pm=is_pm;
    Clock::advance();
    if ((was_pm==1) & (is_pm==0)){
      Calendar::advance();
    }
  };

void ClockCalendar::getSystemTime(){ // WORKING ON LINUX
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
  Clock::setClock (hr,ti->tm_min,ti->tm_sec,pm);
  Calendar::setCalendar(ti->tm_mon,ti->tm_mday,ti->tm_year+1900);
}

// string ClockCalendar::getTime(){
//   int hr, min, sec,pm;
//   Clock::readClock(hr,min,sec,pm);
//   cout << hr<<":"<< min <<":" <<sec << (pm?"PM":"AM") <<endl;
//   string volta = to_string(hr) + ":" + to_string(min) + ":" + to_string(sec) + (pm?"PM":"AM");
//
//   cout << volta;
//   return volta;
// }

void operator++ (ClockCalendar& t){
int was_pm=t.is_pm;
    t.Clock::advance();
    if ((was_pm==1) & (t.is_pm==0)){
      t.Calendar::advance();
    }
};

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
