#ifndef USER_H
# define USER_H
#include <string>
#include <iostream>

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
