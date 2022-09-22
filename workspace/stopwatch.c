#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

//define the global vars --- g refer to -> global
//volatile -> to prevent the compiler from applying any optimization on the code
volatile unsigned char g_seconds=0; //seconds counter
volatile unsigned char g_minutes=0; //minutes counter
volatile unsigned char g_hours=0; //hours counter

void TIMER1_Init(void){
	/* Timer mode
	 1- for non pwm -> FOC1A = 1
	 2- for CTC mode -> WGM12 = 1
	 3- for clock = CPU clock /1024 -> CS10 = CS12 = 1
	 */
	TCCR1A=(1<<FOC1A);
	TCCR1B=(1<<WGM12)|(1<<CS10)|(1<<CS12);
	TCNT1 = 0; //Set the initial value to be 0
	OCR1A = 1000; //set the top (compare) value to be 1 second
	SREG|=(1<<7); //enable interrupt when compare
	TIMSK=(1<<OCIE1A); //match interrupt enable for timer1
}

ISR(TIMER1_COMPA_vect){
	g_seconds++; //increment seconds counter by 1
	//after 60 seconds increment minutes
	if(g_seconds == 60){
		g_seconds = 0; //reset seconds
		g_minutes++; //increment minutes counter by 1
	}
	//after 60 minutes increment hours
	if(g_minutes == 60){
		g_minutes = 0; //reset minutes
		g_hours ++; //increment hours counter by 1
	}
	if(g_hours == 12){ // 12h mode
		g_seconds = 0; //reset seconds
		g_minutes = 0; //reset minutes
		g_hours = 0;   //reset hours
	}
}

//external interrupt 0
void INT0_Init_Reset(void){
	DDRD &=~ (1<<PD2); //define the interrupt 0 pin to be input pin
	PORTD|=(1<<PD2); //internal pull up
	GICR|=(1<<INT0);//enable external interrupt request 0
	MCUCR|=(1<<ISC01); //The falling edge of INT0 generate an interrupt request
	SREG |=(1<<7);
}
ISR(INT0_vect){//reset
	g_seconds = 0;
	g_minutes = 0;
	g_hours = 0;
}

//external interrupt 1
void INT1_Init_Paused(void){
	DDRD &=~(1<<PD3); //define the interrupt 1 pin to be input pin
	MCUCR|=(1<<ISC11)|(1<<ISC10); //The raising edge of INT0 generate an interrupt request
	GICR|=(1<<INT1);//enable external interrupt request 1
	SREG |=(1<<7);
}
ISR(INT1_vect){//paused
	//No clock source (Timer/Counter stopped).
	TCCR1B &=~(1<<CS10)&~(1<<CS11)&~(1<<CS12);
}

//external interrupt 2
void INT2_Init_Resumed(void){
	DDRB &=~ (1<<PB2); //define the interrupt 0 pin to be input pin
	PORTB|=(1<<PB2); //internal pull up
	GICR|=(1<<INT2);//enable external interrupt request 2
	MCUCR &=~(1<<ISC2); //The falling edge of INT2 generate an interrupt request
	SREG |=(1<<7);

}
ISR(INT2_vect){//Resumed
	TCCR1B|=(1<<CS10)|(1<<CS12); //enable clock source again
}

int main(){
	DDRA=0xff; //define the 7 segment to be input pins
	PORTA=0xff; //enable
	DDRC |=0x0f; //first 4 pins decoder
	PORTC = 0x00; // clear the first four bits in PORTC
	INT0_Init_Reset();
	INT1_Init_Paused();
	INT2_Init_Resumed();
	TIMER1_Init();

	while(1){

		//display seconds
		PORTA=(1<<5);
		PORTC = g_seconds % 10; //display first digit of seconds
		_delay_ms(5);
		PORTA=(1<<4);
		PORTC = g_seconds / 10; //display second digit of seconds
		_delay_ms(5);

		//display minutes
		PORTA=(1<<3);
		PORTC = g_minutes % 10; //display first digit of minutes
		_delay_ms(5);
		PORTA=(1<<2);
		PORTC = g_minutes / 10; //display second digit of minutes
		_delay_ms(5);

		//display hours
		PORTA=(1<<1);
		PORTC = g_hours % 10; //display first digit of hours
		_delay_ms(5);
		PORTA=(1<<0);
		PORTC = g_hours / 10; //display second digit of hours
		_delay_ms(5);
	}
}
