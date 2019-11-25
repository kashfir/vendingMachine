#include "User.h"

User::User(){
  username = "";
  password = "";
}

void User::setUser(std::string user){
  username = user;
}
std::string User::getUser(){
  return username;
}
void User::setPassword(std::string pass){
  password = pass;
}
bool User::checkLogin(std::string user,std::string pass){
  if ((username == user) && (password==pass)) return 1;
  else return 0;
}
