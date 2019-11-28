/*
Arquivo: Vector.h
Autor: Thiago Daros Fernandes
Data: 22/11/2019
Descricao: Declara a classe Vector que contem Lista de usuarios cadastrados.
*/
#ifndef VECTOR_H
# define VECTOR_H
#include "User.h"

/*
Classe: Vector
Descricao: Classe que guarda a lista de usuarios que sao administradores da
maquina, com acesso a secao do menu que gera relatorios.
*/
class Vector{
  User vAdmin[20];
  bool valid[20];
public:
  Vector();
  void listVec();
  void includeAdmin(std::string user, std::string password);
  void removeAdmin(std::string user);
  void changePassword(std::string user, std::string password);
  bool login(std::string user, std::string password);
  int countUsers();
  bool userExists(std::string);
};

#endif
