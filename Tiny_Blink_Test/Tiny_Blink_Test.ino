#include <avr\io.h>

int main(void){
	pinMode(0, OUTPUT);
	while(1){
		digitalWrite(0, 1);
		_delay_ms(100);
		digitalWrite(0, 0);
		_delay_ms(100);
	}
	return 0;
}
