#include "clock.h"
#include <string>
#include <iostream>
using namespace std;

Clock::Clock (int h, int m, int s, int pm){
  hr = h;
  min = m;
  sec = s;
  is_pm = pm;
};
void Clock::setClock (int h, int m, int s, int pm){
  hr = h;
  min = m;
  sec = s;
  is_pm = pm;
};
void Clock::readClock (int& h, int& m, int& s, int& pm){
  h = hr;
  s = sec;
  m = min;
  pm = is_pm;
};

void Clock::advance (){
  sec++;
  if (sec>59)
    {
    sec=0;
    min++;
    if(min>59){
      min=0;
      hr++;
      if(hr>11){
        hr=0;
        is_pm = !is_pm;
      }
    }
    }

};
