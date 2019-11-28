/*
Arquivo: clock.h
Autor: Thiago Daros Fernandes
Data: 17/10/2019
Descricao: Declara a classe Clock que define um relogio.
*/
#ifndef CLOCK_H
# define CLOCK_H

/*
Classe: Clock
Descricao: Relogio que guarda hora, minuto, segundo, e AM/PM atraves de objetos
inteiros.
*/
class Clock {
protected:
  int hr, min, sec, is_pm;
public:
  Clock (int h, int m, int s, int pm);
  void setClock (int h, int m, int s, int pm);
  void readClock (int& h, int& m, int& s, int& pm);
  void advance ();
};


#endif
