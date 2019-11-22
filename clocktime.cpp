#include <iostream>
#include <unistd.h>

using namespace std;

class ClockTime {
      int hr;
      int min;
      int seg;
   public:
      void setHr(int);
      void setMin(int);
      void setSeg(int);
      friend ostream& operator<< (ostream&, ClockTime);
      friend void operator++ (ClockTime&);
};


void ClockTime::setHr(int nhr){
	hr = nhr;
}

void ClockTime::setMin(int nmin){
	min = nmin;
}

void ClockTime::setSeg(int nseg){
	seg = nseg;
}

ostream& operator<< (ostream& c, ClockTime t){
	c << t.hr << ":";
	c << t.min << ":";
	c << t.seg;
	return c;
}

void operator++ (ClockTime& t){
   t.seg++;
   if (t.seg == 60){
      t.seg = 0; t.min++;
      if (t.min == 60){
         t.min = 0; t.hr++;
	 if (t.hr == 24)
	    t.hr = 0;
      }
   }
}

int main() {
   ClockTime t;
   t.setHr(9);
   t.setMin(0);
   t.setSeg(0);
   cout << t << endl;
   ++t;
   cout << t << endl;
   while (1) {
      sleep(1);
      system("clear");
      ++t;
      cout << t << endl;
   }
   return 0;
}


