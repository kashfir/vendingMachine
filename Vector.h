#ifndef VECTOR_H
# define VECTOR_H
#include "User.h"

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
