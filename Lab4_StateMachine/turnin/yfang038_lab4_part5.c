/*	Author: yfang038
 *  Partner(s) Name: 
 *	Lab Section:
 *	Assignment: Lab #4  Exercise #5
 *	Exercise Description: [optional - include for your own benefit]
 
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

enum States {Start, Init,KeypadX,KeypadX2, KeypadP, KeypadY,KeypadXSec, Release, Unlock, KeypadP2, Release2, KeypadY2, KeypadXSec2, Release3, Release4, Release5, Release6 } state;
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
			}else if(PINA == 0x01){
				state = KeypadX;
			}else{
				state = Init;
			}
			break;
		case KeypadX:
			if(PINA == 0x01){
				state = KeypadX;
			}else if(PINA == 0x00){
				state = Release2;
			}else{
				state = Init;
			}
			break; 
		case KeypadY:
                        if(PINA == 0x02){
                                state = KeypadY;
                        }else if(PINA == 0x00){
				state = Release3;
			}
			else{
                                state = Init;
                        }
                        break;
		case Release3:
			if(PINA == 0x00){
				state = Release3;
			}else if(PINA == 0x01){
				state = KeypadXSec;
			}else{
				state = Init;
			}
			break;
		case KeypadXSec:
			if(PINA == 0x01 || PINA == 0x00){
				state = Unlock;
			}else{
				state = Init;
			}
			break;
		case Unlock:
			if(PINA == 0x80){
				state = Init;
			}else if(PINA == 0x04){
				state = KeypadP2;
			}
			else{
				state = Unlock;
			}
			break;
		case KeypadP2:
			if(PINA == 0x04){
				state = KeypadP2;
			}else if (PINA == 0x00){
				state = Release4;
			}else{
				state = Unlock;
			}
			break;
		case Release4:
			if(PINA == 0x00){
				state = Release4;
			}else if(PINA == 0x01){
				state = KeypadX2;
			}else{
				state = Unlock;
			}
			break;
		case KeypadX2:
			if(PINA = 0x01){
				state = KeypadX2;
			}else if(PINA == 0x00){
				state = Release5;
			}else{
				state = Unlock;
			}
			break;
		case Release5:
			if(PINA == 0x00){
				state = Release5;
			}else if(PINA == 0x02){
				state = KeypadY2;
			}else{
				state = Unlock;
			}
			break;
		case KeypadY2:
			if (PINA == 0x02){
                      		state = KeypadY2;
                   	}else if (PINA == 0x00) {
                      		state = Release6;
                   	}else {
                     		state = Unlock;
                   	}
                      	break;
		case Release6:
			if(PINA == 0x00){
				state = Release6;
			}else if(PINA == 0x01){
				state = KeypadXSec2;
			}else{
				state = Unlock;
			}
			break;
		case KeypadXSec2:
			if(PINA == 0x01 || PINA == 0x00){
				state = Init;
			}else{
				state = Unlock;
			}
			break;
		case Release2:
			if(PINA == 0x00){
				state = Release2;
			}else if (PINA == 0x04){
				state = Init;
			}else if(PINA == 0x02){
				state = KeypadY;
			}else{
				state = Init;
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
		case KeypadX:
			break;
		case KeypadX2:
			break;
		case KeypadXSec:
                        break;
		case KeypadXSec2:
                        break;
		case KeypadP:
			break;
		case KeypadY:
			break;
		case Release:
			break;
		case KeypadP2:
			break;
		case KeypadY2:
			break;
		case Release2:
			break;
		case Release3:
                        break;
		case Release4:
                        break;
		case Release5:
                        break;
		case Release6:
                        break;
		case Unlock:
			PORTB = 1;
			break;
		default:
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
