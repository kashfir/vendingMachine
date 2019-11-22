#include "Log.h"


void Log::record(ClockCalendar t, float p,string r){
  entry in;
  in.time = t;
  in.price = p;
  in.refri = r;
  database.insertAfterLast(in);
}

void Log::dump(){
  entry buffer;
  while(database.readFirst(buffer)){ // enquanto ha elemento para ser lido
    cout << buffer.time << '\t' << buffer.price << '\t' << buffer.refri << endl;
    database.removeFirst();
  }
  std::cout << "End of dump." << '\n';
}
