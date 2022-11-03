// 2022-11-03
// Version 1

/* 
 * This code will provide the appropriate rotation to balance an inverted pendulum.
 * It does this by specifying the direction and angle of the motor.
 * The L298N Dual H-Bridge driver is used.
 * Both channels are in parallel to increase its current handling.
 * Speed is mapped from -255 to 255, with negatives being CW and positive being CCW.
 * Angle feedback is provided by a potentiometer.
 * To begin the motion, manually move the pendulum to the vertical position and press the start button.
 * 
 * 
 */

#define POT_PIN A0;
#define MOTOR_IN1
#define MOTOR_IN2
#define MOTOR_PWM_PIN
#define START_BUTTON_PIN

double Kp=1;		// value from 0 to 255
double Ki=0;
double Kd=0;
double requiredPosition;

double currentPosition = 0;			//angular position with vertical being zero
double zeroPosition;				// The zero position that is set when the button is pressed. May need hardcoding.
int startFlag = 0;
int button = 0;

unsigned long currentTime = 0;
unsigned long prevTime = 0;
unsigned long dT = 0;
void startButton();
void moveMotor(int speed);

void setup(){
	pinMode(MOTOR_IN1, OUTPUT);
	pinMode(MOTOR_IN2, OUTPUT);
	pinMode(MOTOR_PWM_PIN, OUTPUT);
	pinMode(START_BUTTON_PIN, INPUT);
	pinMode(POT_PIN, INPUT);
	
	Serial.begin(9600);
	
}

void loop(){
	
	while(!startFlag){
		Serial.println("Press the button to start");
		zeroPosition = analogRead(POT_PIN);				// Take zero as the current position
	}
	
	currentPosition = analogRead(POT_PIN);
	currentTime = millis();
	
	error = zeroPosition - currentPosition;
	if (abs(zeroPosition - error) > 100){	// about 30°
		startFlag = 0;
		Serial.println("Fail");
	}
	
	dT = millis() - prevTime;
	
	// P control
	calculatedMotion = Kp * error;
	Serial.println(calculatedMotion);
	moveMotor(calculatedMotion);
	
	// PI control
	//moveMotor(Kp * error_integral);
	
}





void startButton(){
	// If the button is pressed, the flag becomes set
	// The program starts after the button is released.
	// Therefore, holding down the button has no effect.
	// And program waits for button to be released.
	
	static int Button_f = 0;
	Button_f += !digitalRead(START_BUTTON_PIN);

	if (Button_f && digitalRead(START_BUTTON_PIN)){
		startFlag = 1;
		Button_f = 0;
	}
	else {
		startFlag = 0;
	}
}

void moveMotor(int speed){
	if (speed > 0){
		digitalWrite(Motor_in1, LOW);
		digitalWrite(Motor_in2, HIGH);
		analogWrite(MOTOR_PWM_PIN, speed);
	}
	
	if (speed < 0){
		digitalWrite(Motor_in1, HIGH);
		digitalWrite(Motor_in2, LOW);
		analogWrite(MOTOR_PWM_PIN, speed);
	}
	
	if (speed == 0){
		digitalWrite(Motor_in1, LOW);
		digitalWrite(Motor_in2, LOW);
	}
}