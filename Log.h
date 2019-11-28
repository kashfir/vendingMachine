/*
Arquivo: Log.h
Autor: Thiago Daros Fernandes
Data: 15/11/2019
Descricao: Este arquivo e responsavel por declarar a classe Log que encapsula
uma lista para formar o log da maquina. Tambem declara a estrutura day period.
*/

#ifndef LOG_H
#define LOG_H
#include "List.h"

/*
Classe: dayPeriod
Descricao: Declara a estrutura day period que separa o dia em partes iguais
 de 6 horas para gerar, posteriormente, o relatorio de vendas por periodo.
*/
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


/*
Classe: Log
Descricao: Possui um objeto List database que guarda dados do tipo "entry",
previamente declarado no arquivo Node.h. Possui funcoes que geral relatorios e
de gravar uma nova entrada no log.
*/
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
