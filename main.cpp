#include "InterfacePC.h"
#include <thread>


int main(){
   InterfacePC  inter;
   while(1){
      inter.printMenu();
      inter.inputCommand();
   }



}
