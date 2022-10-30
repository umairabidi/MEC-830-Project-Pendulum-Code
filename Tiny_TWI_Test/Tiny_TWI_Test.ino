#include <avr\io.h>
#include <TinyWireS.h>

/*
 * This code is meant to test comms
 * 2-wire mode on the Universal Serial Interface is TWI compatible
 * Which is I2C, essentially
 * This device will be a slave device only.
 * It will send a value when requested
 * 
 * Pins 5 and 7 are used
 * Pin 5 = PB0 = SDA
 * Pin 7 = PB2 = SCL 
*/


#define I2C_SLAVE_ADDR  0x26
uint8_t master_data[16];




int value_to_send = 0;

int main(void){

	TinyWireS.begin(13);    	// I2C address            
	TinyWireS.onReceive(receiveEvent);	// Call this function
  
	
	
	return 0;
}

void receiveEvent(int howMany){
	value_to_send = TinyWireS.receive();
}
