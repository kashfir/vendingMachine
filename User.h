/*
Arquivo: User.h
Autor: Thiago Daros Fernandes
Data: 22/11/2019
Descricao: Declara a classe User que contem dados de um usuario com acesso ao
menu que gera relatorios de vendas da maquina.
*/


#ifndef USER_H
# define USER_H
#include <string>
#include <iostream>

/*
Classe: User
Descricao: Classe que guarda informacoes de login de usuario.
*/
class User {
  std::string username, password;
public:
  User();
  void setUser(std::string user);
  std::string getUser();
  void setPassword(std::string);
  bool checkLogin(std::string,std::string);
};


#endif
