#ifndef LOG_H
#define LOG_H
#include "List.h"

class dayPeriod{ //
public:
  int dawn, morning, afternoon, evening;
  dayPeriod(){
    dawn = 0;
    morning = 0;
    afternoon = 0;
    evening = 0;
  }
};

class Log {
  List<entry> database;
public:
  void record(ClockCalendar t, float p, std::string r);
  void dump();
  float getSales();
  void readSalesCount(int&, int&);
  dayPeriod maxSalesPeriod();
};


#endif
