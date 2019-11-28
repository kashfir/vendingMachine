#include "InterfacePC.h"


InterfacePC* ptr2FuncHandler;

void timeCountWrapper(){
  ptr2FuncHandler->InterfacePC::timeCount();
}
void updateSMWrapper(){
  ptr2FuncHandler->InterfacePC::updateSM();
}
void updateInputWrapper(){
  ptr2FuncHandler->InterfacePC::updateInput();
}

int main(){
   InterfacePC inter;
   ptr2FuncHandler = &inter;
   inter.addTask(timeCountWrapper,1000);
   inter.addTask(updateSMWrapper,100);
   while(1){

   }
}
