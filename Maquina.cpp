#include "Maquina.h"

#define S000	0x1
#define S025	0x2
#define S050	0x4
#define S075	0x8
#define S100	0x10
#define S125	0x20
#define S150	0x40

#define D025 0x1
#define D050 0x2
#define D100 0x4
#define LMEET 0x8
#define LETIRPS 0x10
#define INSUFF 0x20

#define Nada 0x1
#define M025 0x2
#define M050 0x4
#define M100 0x8
#define D050 0x2
#define DEV 0x10
#define MEET	0x20
#define ETIRPS	0x40

Maquina::Maquina(){
	state = 1;
	out = 0;
}

char Maquina::nextState(char cmd){

switch (cmd){
	case 0:  break;
	case Nada: break;
	case M025:	{
		switch (state){
			case S000: state = S025; break;
			case S025: state = S050; break;
			case S050: state = S075; break;
			case S075: state = S100; break;
			case S100: state = S125; break;
			case S125: state = S150; break;
			case S150: {
				state = S150;
				out = D025;}  break;
				}
			}  break;
	case M050:	{
		switch (state){
			case S000: state = S050; break;
			case S025: state = S075; break;
			case S050: state = S100; break;
			case S075: state = S125; break;
			case S100: state = S150; break;
			case S125: {
				state = S150;
				out = D025;} break;
			case S150: {
				state = S150;
				out = D050;} break;
				}
			}  break;
	case M100:	{
		switch (state){
			case S000: state = S100; break;
			case S025: state = S125; break;
			case S050: state = S150; break;
			case S075: {
				state = S150;
				out = D025;}  break;
			case S100: {
				state = S150;
				out = D050;}  break;
			case S125: {
				state = S150;
				out = (D025 + D050);
								}  break;
			case S150: {
				state = S150;
				out = D100;}  break;
									}
							}  break;
	case DEV:	{
		switch (state){
			case S000:  break;
			case S025: {
				state = S000;
				out = D025;}  break;
			case S050: {
				state = S000;
				out = D050;}  break;
			case S075: {
				state = S000;
				out = D025 + D050;}  break;
			case S100: {
				state = S000;
				out = D100;} break;
			case S125: {
				state = S000;
				out = D025 + D100;} break;
			case S150: {
				state = S000;
				out = D050 + D100;} break;
			}
		} break;
	case MEET:	{
		switch (state){
			case S000: state = S000; out = INSUFF; break;
			case S025: state = S025; out = INSUFF; break;
			case S050: state = S050; out = INSUFF; break;
			case S075: state = S075; out = INSUFF; break;
			case S100: state = S100; out = INSUFF; break;
			case S125: state = S125; out = INSUFF; break;
			case S150: {
				state = S000;
				out = LMEET;}  break;
				}
			}  break;
	case ETIRPS:	{
		switch (state){
			case S000: state = S000; out = INSUFF; break;
			case S025: state = S025; out = INSUFF; break;
			case S050: state = S050; out = INSUFF; break;
			case S075: state = S075; out = INSUFF; break;
			case S100: state = S100; out = INSUFF; break;
			case S125: state = S125; out = INSUFF; break;
			case S150: {
				state = S000;
				out = LETIRPS;}  break;
				}
			}  break;

		}

sendCommand(out);
out = 0;
return state;
}
