#include "Log.h"


void Log::record(ClockCalendar t, float p, std::string r){
  entry in;
  in.time = t;
  in.price = p;
  in.refri = r;
  database.insertAfterLast(in);
}

void Log::dump(){
  entry buffer;
  while(database.readFirst(buffer)){ // enquanto ha elemento para ser lido
    std::cout << buffer.time << '\t' << buffer.price << '\t' << buffer.refri << std::endl;
    database.removeFirst();
  }
  std::cout << "End of dump." << '\n';
}

float Log::getSales(){                    // le a database e retorna um float com o valor total das vendas
  List<entry> bufferList;                 //lista buffer para guardar os elementos temporariamente
  entry reading;                          //elemento de cadastro acessorio
  float saleSum = 0;                      // guarda o total das vendas
  while(database.readFirst(reading)){     // enquanto ha elemento para ser lido na database
    saleSum += reading.price;             // soma o valor de cada elemento vendido
    bufferList.insertAfterLast(reading);  // joga o elemento na lista buffer
    database.removeFirst();               // remove o elemento
  }
  while(bufferList.readFirst(reading)){ //repassa a lista buffer para a database
  database.insertAfterLast(reading);
  bufferList.removeFirst();
  }
  return saleSum;                         //retorna total das vendas
}


void Log::readSalesCount(int& meet, int& etirps){
  List<entry> bufferList;
  meet = 0;
  etirps = 0;
  entry reading;                          //elemento buffer de cadastro
  while(database.readFirst(reading)){     // enquanto ha elemento para ser lido na database
    if (reading.refri == "MEET") meet++;            // soma o refrigerante
    else if (reading.refri == "ETIRPS") etirps++;
    bufferList.insertAfterLast(reading);  // joga o elemento na lista buffer
    database.removeFirst();               // remove o elemento
  }
  while(bufferList.readFirst(reading)){ //repassa a lista buffer para a database
  database.insertAfterLast(reading);
  bufferList.removeFirst();
  }
}

dayPeriod Log::maxSalesPeriod(){
  List<entry> bufferList;
  dayPeriod count;
  int hr, min, sec, pm;
  entry reading;                        //elemento buffer de cadastro
  while(database.readFirst(reading)){     // enquanto ha elemento para ser lido na database
    reading.time.readClock(hr,min,sec,pm);
    if (hr<6 && !pm) count.dawn++;
    else if (hr>=6 && !pm) count.morning++;
    else if (hr<6 && pm) count.afternoon++;
    else count.evening++;
    bufferList.insertAfterLast(reading);  // joga o elemento na lista buffer
    database.removeFirst();               // remove o elemento
  }
  while(bufferList.readFirst(reading)){ //repassa a lista buffer para a database
  database.insertAfterLast(reading);
  bufferList.removeFirst();
  }
  return count;
}
