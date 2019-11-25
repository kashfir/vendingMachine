#include "Vector.h"

// Construtor
Vector::Vector() {
    for(int i = 0; i < 20; i++) {
        valid[i] = 0;
    }
}

void Vector::listVec() {
  std::cout << "Usuarios cadastrados:" << '\n';
    for (int i = 0; i < 20; i++) {
        if(valid[i]) {
           std::cout << vAdmin[i].getUser() << std::endl;
        }
    }
}

void Vector::includeAdmin(std::string user, std::string password) {
    int i = 0;
    int guardaPosicao;
    bool sai = false;
    bool termina = false;
    do {
        for (int x = 0; x < 20; x++) {
            if (user == vAdmin[x].getUser()) {
                std::cout << "Usuario ja cadastrado!" << std::endl;
                sai = true;
            }
        }
        if (!sai && !valid[i]) {
            guardaPosicao = i;
            termina = true;
        }
        i++;
    } while (i < 20 && !sai && !termina);
    // Caso sai = true, o encerramento foi devido a um problema de usuario
    // duplicada, nao podendo ser gravado os dados no objeto
    // A flag 'termina' existe para direcionar o fluxo caso haja um espaco livre no vetor valid[i]
    if (!sai && termina) {
        vAdmin[guardaPosicao].setUser(user);
        vAdmin[guardaPosicao].setPassword(password);
        valid[guardaPosicao] = 1; // Indica o preenchimeto de um objeto
    }
}

void Vector::removeAdmin(std::string user) {
    bool found = 0;
    int i = 0;
    while (!found && i<20) {
        if (user == vAdmin[i].getUser()) {
            found = 1;
            valid[i] = 0;
             vAdmin[i].setUser(""); //Numero invalid para liberar o repreenchimento
            std::cout << "Usuario "<<user <<" removido!\n\n";
        }
        i++;
    }
    if (!found) std::cout << "Usuario nao encontrado! Tente novamente.\n\n";
}

// Alteracao das notas de um determinado aluno
void Vector::changePassword(std::string user, std::string password) {
    bool found = 0;
    int i = 0;
    while (!found && i < 20) {
        if (user == vAdmin[i].getUser()) {
            found = 1;
            vAdmin[i].setPassword(password);
        }
        i++;
    }
    if (!found) std::cout << "Usuario nao encontrado! Tente novamente.\n\n";
}

bool Vector::login(std::string user, std::string password) {
    bool found = 0;
    int i = 0;
    while (!found && i < 20) {
        if (user == vAdmin[i].getUser()) {
            found = 1;
            if(!(vAdmin[i].checkLogin(user,password))){
              std::cout << "Senha incorreta!" << '\n';
              return 0;
            }
            std::cout << "Sucesso!" << '\n';
            return 1;
        }
        i++;
    }
    if (!found) std::cout << "Usuario nao encontrado! Tente novamente.\n\n";
    return 0;
}

int Vector::countUsers(){
  int count = 0;
  for (int i = 0 ; i < 20 ; i++){
    count += valid[i];
  }
  return count;
}

bool Vector::userExists(std::string user){
  for (int x = 0; x < 20; x++) {
      if (user == vAdmin[x].getUser()) {
          return 1;
      }

    }
  return 0;
}
