#include "calendar.h"
#include <iostream>

using namespace std;

Calendar::Calendar (int m, int d, int y){
  mo = m;
  day = d;
  yr = y;
};
void Calendar::setCalendar (int m, int d, int y){
  mo = m;
  day = d;
  yr = y;
};
void Calendar::readCalendar (int& m, int& d, int& y){
  m = mo;
  d = day;
  y = yr;
};
void Calendar::advance (){
  day++;
  if (day>30){
    day = 1;
    mo++;
    if (mo>12){
      mo = 1;
      yr++;
    }

  }
};
