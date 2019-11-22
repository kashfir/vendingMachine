#ifndef CALENDAR_H
# define CALENDAR_H

class Calendar {
protected:
  int mo, day, yr;
public:
  Calendar (int m, int d, int y);
  void setCalendar (int m, int d, int y);
  void readCalendar (int& m, int& d, int& y);
  void printCalendar();
  void advance ();
};



#endif
