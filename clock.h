#ifndef CLOCK_H
# define CLOCK_H

class Clock {
protected:
  int hr, min, sec, is_pm;
public:
  Clock (int h, int m, int s, int pm);
  void setClock (int h, int m, int s, int pm);
  void readClock (int& h, int& m, int& s, int& pm);
  void printClock ();
  // friend void operator++ (Clock&);
  void advance ();
};


#endif
