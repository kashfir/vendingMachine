/*
Arquivo: Maquina.h
Autor: Thiago Daros Fernandes
Data: 23/10/2019
Descricao: Declara a classe Maquina que contem a maquina de estados.
*/

#ifndef MAQUINA_H
#define MAQUINA_H


/*
Classe: Maquina
Descricao: Maquina de estados que resolve o estado atraves de nextState e
retorna o comando de saida atraves de funcao abstrata sendCommand.
*/
class Maquina {
		char state, out;
	public:
		Maquina();
		char getState(){return state;}
		char nextState(char cmd);
		virtual void sendCommand(char cmd) = 0;

};
#endif // MAQUINA
