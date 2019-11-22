#ifndef LOG_H
#define LOG_H
#include "List.h"

class Log {
  List<entry> database;
public:
  void record(ClockCalendar t, float p,string r);
  void dump();
};


#endif
