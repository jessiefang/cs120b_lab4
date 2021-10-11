/*	Author: yfang038
 *  Partner(s) Name: 
 *	Lab Section:
 *	Assignment: Lab #4  Exercise #2
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

enum States {Start, Init, Increment, Decrement, Reset, On_Increment, On_Decrement} state;
unsigned char cnt = 0x07;
void Tick() {
	switch(state){
		case Start:
			state = Init;
			break;
		case Init:
			if (PINA == 0x03){
				state = Reset;
			}
			else if(PINA == 0x01){
				state = On_Increment;
			}
			else if(PINA == 0x02){
				state = On_Decrement;
			}
			break;
		case Increment:
			if(PINA == 0x01){
				state = Increment;
			}
			else if (PINA == 0x00){
				state = Init;
			}else if(PINA == 0x02){
				state = On_Decrement;
			}
			else if (PINA == 0x03){
				PORTC = 0x00;
				state = Reset;
			}
                        break;
		case On_Increment:
			state = Increment;
			break; 
		case Decrement:
                        if(PINA == 0x02){
                                state = Decrement;
                        }else if (PINA == 0x00){
                                state = Init;
                        }else if (PINA == 0x01){
				state = On_Increment;
			}
			else if (PINA == 0x03){
                                state = Reset;
                        }
                        break;
		case On_Decrement:
                        state = Decrement;
	                break;
		case Reset:
			if(PINA == 0x03){
				state = Reset;
			}else if(PINA == 0x00){
				state = Init;
			}
			else{
				state = Init;
			}
			break;
		 default:
			state = Start;
			break;
	}
	switch(state){
		case Start:
			PORTC = 0x07;
			break;
		case Init:
			break;
		case Increment:
			break;
		case On_Increment:
			if(cnt < 0x09){
				cnt++;
			}
			break;
		case Decrement:
			break;
		case On_Decrement:
			if(cnt > 0x00){
				cnt--;
			}
			break;
		case Reset:
			cnt = 0;
			PORTC = 0x00;
			break;
		default:
			PORTC = 0x07;
			break;
	}
}


int main(void) {
    /* Insert DDR and PORT initializations */
	DDRA = 0x00; PORTA = 0xFF;
	DDRC = 0xFF; PORTC = 0x00;
	cnt = 7;
    /* Insert your solution below */
    while (1) {
	Tick();
 	PORTC = cnt;
    }
    return 1;
}
