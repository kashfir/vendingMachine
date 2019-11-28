/*
Arquivo: calendar.h
Autor: Thiago Daros Fernandes
Data: 17/10/2019
Descricao: Declara a classe Calendar que define um calendario.
*/
#ifndef CALENDAR_H
# define CALENDAR_H
/*
Classe: Calendar
Descricao: Calendario que guarda mes, dia e ano, atraves de objetos
inteiros.
*/
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
