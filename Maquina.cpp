#include "Maquina.h"
/*
Estado Atual	Nada	M025	M050	M100	DEV	MEET	ETIRPS

S000		S000	S025	S050	S100	S000	S000	S000


S025		S025	S050	S075	S125	S000	S025	S025
						D025

S050		S050	S075	S100	S150	S000	S050	S050
						D050

S075		S075	S100	S125	S150	S000	S075	S075
					D025	D025
						D050

S100		S100	S125	S150	S150	S000	S100	S100
					D050	D100

S125		S125	S150	S150	S150	S000	S125	S125
				D025	D025	D025
					D050	D100

S150		S150	S150	S150	S150	S000	S000	S000
			D025	D050	D100	D050	LMEET	LETIRPS
						D100
ESTADOS:

S000: 00000001	0x1
S025: 00000010	0x2
S050: 00000100	0x4
S075: 00001000	0x8
S100: 00010000	0x10
S125: 00100000	0x20
S150: 01000000	0x40

ENTRADAS:

Nada
M025
M050
M100
DEV
MEET
ETIRPS

SAIDAS:

D025: 	00000001	0x1
D050: 	00000010	0x2
D100:	00000100	0x4
LMEET:	00001000	0x8
LETIRPS:00010000	0x10
INSUFF: 00100000 0x20

*/

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
	case Nada: state = 0; break;
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
