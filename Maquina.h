#ifndef MAQUINA
#define MAQUINA


class Maquina {
		char state, out;
	public:
		Maquina();
		char getState(){return state;}
		char nextState(char cmd);
		virtual void sendCommand(char cmd) = 0;

};


#endif // MAQUINA
