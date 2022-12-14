#include <avr\io.h>

// PCINT pin
// DDR IO
// ISR for PCINT
// SPI pins for programming wtih Arduino
// Internal RC oscillator	(already done with bootloader)
// USI (2-wire mode, I²C compatible)

/* 
 *  This code takes in pulses from the incremental encoder and calculates the angle based on those values.
 *  Each pulse is 4.5° of motion
 *  
 *  Pinout:
 *  PCINT3 on Pin 2	(PB3) (IRE 1 green)
 *  PCINT4 on PIN 3	(PB4) (IRE 2 blue)
 *      DI on Pin 6 (PB1) (Button input)
 */


// I have decided not to continue with this.
// I2C implementation is unncessarily complicated to implement.
// and I don't even need to.
// The Arduino should be good enough since I'm using interrupts anyways... right?
// we shall see.



#define IRE1 PB3
#define IRE2 PB4
#define ButtonPin PB1
#define CLOCKWISE 1
#define COUNTERCLOCKWISE -1

// Flags for the IRE
volatile int flag_IRE1 = 1;
volatile int flag_IRE2 = 1;
volatile int direction = 0;

ISR (PCINT0_vect){	// all PCINT pins share the same vector
    // PCIF flag in GIFR is set on any PCINT
	direction = ((PINB & (1<<IRE1)) <<1)^(PINB & (1<<IRE2))?FORWARD:REVERSE;
}


int main(void){

	// Pin Setup
	DDRB &= ~(1<<DDB1);				// Input
	DDRB |= (1<<DDB3)|(1<<DDB4);	// Output

	// PCINT Setup
	GIMSK |= (1<<PCIE);					// General enable
	PCMSK |= (1<<PCINT3)|(1<<PCINT4);	// Pin-specific enable

	// Global interrupt enable
	//SREG |= (1<<I);	// In the past I have had issues with this line
	sei();
	// cli() to prevent interrupts

	double angle = 0;
	// void loop() in Arduino
	while(1){
		angle;
	}
		
	return 0;
}
