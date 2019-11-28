/*
Arquivo: ClockCalendar.h
Autor: Thiago Daros Fernandes
Data: 17/10/2019
Descricao: Declara a classe ClockCalendar que define um relogio com calendario.
*/
#ifndef CLOCKCALENDAR_H
# define CLOCKCALENDAR_H
#include "clock.h"
#include "calendar.h"
#include <iostream>
#include <string>

/*
Classe: ClockCalendar
Descricao: Herda Clock e Calendar para formar uma estrutura que contem data e hora.
Contem sobrecarga de operador ++ para o avanco do menor elemento de tempo (segundo),
e do operador << para retornar um std::ostream, utilizado para debugging.
*/
class ClockCalendar : public Clock, public Calendar {
 public:
    ClockCalendar () : Clock (0, 0, 0, 0), Calendar (0, 0, 0){};
  	ClockCalendar (int mt, int d, int y, int h, int m, int s, int pm) : Clock (h, m, s, pm), Calendar (mt, d, y){};
  	void advance();
	friend void operator++ (ClockCalendar& t);
	friend std::ostream& operator<< (std::ostream&, ClockCalendar);
};
#endif
