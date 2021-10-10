/*	Author: yfang038
 *  Partner(s) Name: 
 *	Lab Section:
 *	Assignment: Lab #4  Exercise #3
 *	Exercise Description: [optional - include for your own benefit]
 
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

enum States {Start, Init, KeypadP, KeypadY, Release, Unlock } state;
void Tick() {
	switch(state){
		case Start:
			state = Init;
			break;
		case Init:
			if(PINA == 0x04){
				state = KeypadP;
			}
			else{
				state = Init;
			}
			break;
		case KeypadP:
			if(PINA == 0x04){
				state = KeypadP;
			}
			else if (PINA == 0x00){
				state = Release;
			}
			else{
				state = Init;
			}
                        break;
		case Release:
			if(PINA == 0x00){
				state = Release;
			}else if(PINA == 0x04){
				state = Init;
			}else if(PINA == 0x02){
				state = KeypadY;
			}else{
				state = Init;
			}
			break; 
		case KeypadY:
                        if(PINA == 0x02){
                                state = Unlock;
                        }else{
                                state = Init;
                        }
                        break;
		case Unlock:
			if(PINA == 0x80){
				state = Init;
			}else{
				state = Unlock;
			}
			break;
		 default:
			state = Start;
			break;
	}
	switch(state){
		case Start:
			PORTB = 0x00;
			break;
		case Init:
			PORTB = 0x00;
			break;
		case KeypadP:
			break;
		case KeypadY:
			break;
		case Release:
			break;
		case Unlock:
			PORTB = 1;
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
    /* Insert your solution below */
    while (1) {
	Tick();
    }
    return 1;
}
