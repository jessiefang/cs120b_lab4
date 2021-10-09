/*	Author: yfang038
 *  Partner(s) Name: 
 *	Lab Section:
 *	Assignment: Lab #  Exercise #
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

enum States {Start, On_Press, On_Release, OFF_Press, OFF_Release} state;
void Tick() {
	switch(state){
		case Start:
			state = On_Press;
			break;
		case On_Press:
			if(PINA == 0x01){
				state = On_Press;
			}else{
				state = On_Release;
			}
			break;
		case On_Release:
                        if(PINA == 0x01){
                                state = OFF_Press;
                        }else{
                                state = On_Release;
                        }
                        break; 
		case OFF_Press:
                        if(PINA == 0x01){
                                state = OFF_Press;
                        }else{
                                state = OFF_Release;
                        }
                        break;
		case OFF_Release:
                        if(PINA == 0x01){
                                state = On_Press;
                        }else{
                                state = OFF_Release;
                        }
                        break;
		 default:
			state = Start;
			break;
	}
	switch(state){
		case Start:
			PORTB = 0x01;
			break;
		case On_Press:
			PORTB = 0x01;
			break;
		case On_Release:
			break;
		case OFF_Press:
			PORTB = 0x02;
			break;
		case OFF_Release:
			break;
		default:
			PORTB = 0x01;
			break;
	}
}


int main(void) {
    /* Insert DDR and PORT initializations */
	DDRA = 0x00; PORTA = 0xFF;
	DDRB = 0xFF; PORTB = 0x00;
    /* Insert your solution below */
    while (1) {
	Tick();
    }
    return 1;
}
