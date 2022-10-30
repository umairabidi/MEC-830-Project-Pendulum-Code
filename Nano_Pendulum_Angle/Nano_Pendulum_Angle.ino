
/*
 * This code just tests reading from the incremental encoder
 * and determining the angle from the read.
 * IRE = incremental rotary encoder
 * IRE1 is on digital pin 5	which is PD5 or PCINT21
 * IRE2 is on digital pin 6 which is PD6 or PCINT22
 * the resolution of the IRE is 4.5 degrees.
 * 20 clicks per revolution
 * and 2 pulses per click
 * and 2 channels
 * 360°/(20*2*2) = 4.5°
 */
 

#define IRE1 PD5
#define IRE2 PD6
#define CLOCKWISE 1
#define COUNTERCLOCKWISE -1
#define RESOLUTION 4.5

volatile int interrupt_flag = 0;
unsigned long prev_time = 0;
double angle = 0;

volatile int IRE_Direction = 0;
ISR (PCINT2_vect){	// all PCINT23~16 share the same vector
	interrupt_flag = 1;
	// The interrupt flag is the PCIF2 bit in PCIFR but we don't need this
}

void setup(){
	// Pin Setup
	DDRD &= ~((1<<DDD5)|(1<<DDD6));	// Input

	// PCINT Setup
	PCICR |= (1<<PCIE2);					// General enable (for PCINT23~16)
	//PCMSK2 |= (1<<PCINT21)|(1<<PCINT22);	// Pin-specific enable
	PCMSK2 |= (1<<PCINT21);	// Pin-specific enable

	// Global interrupt enable
	//SREG |= (1<<I);	// In the past I have had issues with this line
	sei();

	Serial.begin(115200);
}

void loop(){

	if (interrupt_flag == 1){
		IRE_Direction = ((PIND & (1<<IRE1)) <<1)^(PIND & (1<<IRE2))?CLOCKWISE:COUNTERCLOCKWISE;
		// Based on truth table for pin state vs direction (IRE1 XOR IRE2 = CW)
		angle += RESOLUTION*IRE_Direction;
		interrupt_flag = 0;
	}

	// print every half second only (but continuously be reading from encoder)
	if(millis() - prev_time >= 500){
		cli();
		Serial.println(angle);
		sei();
		prev_time = millis();
	}
}
