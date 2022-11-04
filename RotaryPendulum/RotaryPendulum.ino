// 2022-11-04
// Version 2

/* 
 * This code will provide the appropriate rotation to balance an inverted pendulum.
 * It does this by specifying the direction and angle of the motor.
 * The L298N Dual H-Bridge driver is used.
 * Speed is mapped from -255 to 255, with negatives being CW and positive being CCW. (?)
 * Angle feedback is provided by a potentiometer.
 * To begin the motion, manually move the pendulum to the vertical position and press the start button.
 * The motor is powered with a 12 V supply for parameters Kp = 30 and Ki = 10
 * 
 */

#define POT_PIN 	A0
#define MOTOR_IN1	7
#define MOTOR_IN2	8
#define MOTOR_PWM_PIN	9
#define START_BUTTON_PIN	A4

double Kp=40;
double Ki=40;
double Kd=1;

double requiredPosition;
double currentPosition;		//angular position
double zeroPosition;		// The zero position that is set when the button is pressed.
int startFlag = 0;			// Can we start the program?
int button = 0;				// Button state
double errorPos;			// position error
double errorInt;			// integral of error (trapezoid approximation)
double errorDer;			// Derivative of error (secant approximation)
double prevPosition;		// used for I and D calculations
double calculatedMotion;	// Final output motion required for the motor
unsigned long currentTime = 0;
unsigned long prevTime = 0;
unsigned long dT = 0;


void startButton();
void moveMotor(int Speed);

void setup(){
	pinMode(MOTOR_IN1, OUTPUT);
	pinMode(MOTOR_IN2, OUTPUT);
	pinMode(MOTOR_PWM_PIN, OUTPUT);
	pinMode(START_BUTTON_PIN, INPUT);
	pinMode(POT_PIN, INPUT);
	
	//Serial.begin(57600);
	
}

void loop(){
	while(!startFlag){
		moveMotor(0);	//Brake immediately
		prevTime = 0;			// reset time
		errorInt = 0;
		errorDer = 0;
		prevPosition = zeroPosition;
		zeroPosition = analogRead(POT_PIN);				// Take zero as the current position
		startButton();
	}
	
	currentPosition = analogRead(POT_PIN);
	currentTime = millis();
	
	errorPos = zeroPosition - currentPosition;
	if (abs(errorPos) > 150){	// about 10 per 3°, 150 is 45°
		startFlag = 0;
	}
	
	// PI control
	dT = currentTime - prevTime;	
	errorInt = dT*(0.5)*(currentPosition + prevPosition);
	//errorDer = abs(currentPosition - prevPosition)/dT;		// This breaks the code entirely

	calculatedMotion = Kp*errorPos + Ki*errorInt + Kd*errorDer;
	moveMotor((int)calculatedMotion);

	prevPosition = currentPosition;
	prevTime = currentTime;
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
		Serial.println("pressed");
	}
	else {
		startFlag = 0;
	}
}

void moveMotor(int Speed){
	if (Speed > 0){
		if (Speed > 255){
			Speed = 255;
		}
		digitalWrite(MOTOR_IN1, LOW);
		digitalWrite(MOTOR_IN2, HIGH);
		analogWrite(MOTOR_PWM_PIN, Speed);
	}
	
	if (Speed < 0){
		if (Speed < -255){
			Speed = -255;
		}		
		digitalWrite(MOTOR_IN1, HIGH);
		digitalWrite(MOTOR_IN2, LOW);
		analogWrite(MOTOR_PWM_PIN, -Speed);
	}
	
	if (Speed == 0){
		digitalWrite(MOTOR_IN1, LOW);
		digitalWrite(MOTOR_IN2, LOW);
	}
}
