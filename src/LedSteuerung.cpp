	#include "LedSteuerung.hpp"


LedSteuerung::LedSteuerung(){
	wiringPiSetup();
	pinMode(LeftForwardPin, OUTPUT);
	pinMode(LeftBackwardPin, OUTPUT);
	pinMode(RightForwardPin, OUTPUT);
	pinMode(RightBackwardPin, OUTPUT);

	digitalWrite(LeftForwardPin, HIGH);
	digitalWrite(LeftBackwardPin, LOW);
	digitalWrite(RightForwardPin, HIGH);
	digitalWrite(RightBackwardPin, LOW);

	forward = true;

	LeftSpeed = 0;
	RightSpeed = 0;
	
	softPwmCreate(LeftPwmPin, 0, LeftPwmRange);
	softPwmCreate(RightPwmPin, 0, RightPwmRange);
	}

void LedSteuerung::faster(){
	if (forward)
	{
		LeftSpeed = ((LeftSpeed + acceleration) < LeftPwmRange) ? LeftSpeed + acceleration : LeftPwmRange; 
		RightSpeed = ((RightSpeed + acceleration) < RightPwmRange) ? RightSpeed + acceleration : RightPwmRange;
	}
	else
	{
		LeftSpeed = ((LeftSpeed - acceleration) > -LeftPwmRange) ? LeftSpeed - acceleration : -LeftPwmRange; 
		RightSpeed = ((RightSpeed + acceleration) > -RightPwmRange) ? RightSpeed - acceleration : -RightPwmRange;
	}
	this->writeOut();
}

void LedSteuerung::slower(void){
	if (forward)
	{
		LeftSpeed = ((LeftSpeed - brakeForce) < 1) ?  0 : LeftSpeed - brakeForce; 
		RightSpeed = ((RightSpeed - brakeForce) < 1) ? 0 : RightSpeed - brakeForce;
	}
	else
	{
		LeftSpeed = ((LeftSpeed + brakeForce) > -1) ?  0 : LeftSpeed + brakeForce; 
		RightSpeed = ((RightSpeed + brakeForce) > -1) ? 0 : RightSpeed + brakeForce;
	}
	this->writeOut();
}

void LedSteuerung::right(void){
		LeftSpeed -= steeringAngle;

	RightSpeed = ((RightSpeed + steeringAngle) < RightPwmRange) ? RightSpeed + steeringAngle : RightPwmRange;

	this->writeOut();
}

void LedSteuerung::left(void){
		RightSpeed -= steeringAngle;

	LeftSpeed = ((LeftSpeed + steeringAngle) < LeftPwmRange) ? LeftSpeed + steeringAngle : LeftPwmRange;

	this->writeOut();
}

void LedSteuerung::stop(void){
	LeftSpeed = 0;
	RightSpeed = 0;
	this->writeOut();
}

void LedSteuerung::straight(void){
	int meanSpeed = (LeftSpeed + RightSpeed) / 2;
	LeftSpeed = meanSpeed;
	RightSpeed = meanSpeed;
	this->writeOut();
}

void LedSteuerung::changeDirection(void){
	forward = !forward;
	LeftSpeed = LeftSpeed * -1;
	RightSpeed = RightSpeed * -1;
	this->writeOut();
}

void LedSteuerung::changeDirectionLeft(void){
	LeftSpeed = LeftSpeed * -1;
	this->writeOut();
}

void LedSteuerung::changeDirectionRight(void){
	RightSpeed = RightSpeed * -1;
	this->writeOut();
}

void LedSteuerung::setLeftSpeed(int speed){
	if (0 < speed < LeftPwmRange){
		LeftSpeed = speed;
		this->writeOut();
	}
}

void LedSteuerung::setRightSpeed(int speed){
	if (0 < speed < RightPwmRange){
		RightSpeed = speed;
		this->writeOut();
	}
}

void LedSteuerung::setSpeed(int speed)
{
			printw("wwwww");
	int speedChange  = speed - (RightSpeed + LeftSpeed) / 2;

	printw("%d", speedChange);
	if (speedChange > 0)
	{
		for ( int i = 0 ; i < speedChange; i + acceleration)
		{
			this->faster();
			this->writeOut();
			usleep(10000);
		}
	}
	else
	{
		for ( int i = 0 ; i < speedChange; i + brakeForce)
		{
			this->slower();
			this->writeOut();
			usleep(10000);		
		}
	}
}
	
void LedSteuerung::writeOut(void){
	if(LeftSpeed > 0)
	{
		digitalWrite(LeftForwardPin, HIGH);
		digitalWrite(LeftBackwardPin, LOW);
	}
	else
	{
		digitalWrite(LeftForwardPin, LOW);
		digitalWrite(LeftBackwardPin, HIGH);
	}

	if(RightSpeed > 0)
	{
		digitalWrite(RightForwardPin, HIGH);
		digitalWrite(RightBackwardPin, LOW);
	}
	else{
		digitalWrite(RightForwardPin, LOW);
		digitalWrite(RightBackwardPin, HIGH);
	}

	softPwmWrite(LeftPwmPin, fabs(LeftSpeed));
	softPwmWrite(RightPwmPin, fabs(RightSpeed));
}
	
LedSteuerung::~LedSteuerung(){
	digitalWrite(LeftForwardPin, LOW);
	digitalWrite(LeftBackwardPin, LOW);
	digitalWrite(RightForwardPin, LOW);
	digitalWrite(RightBackwardPin, LOW);

	softPwmWrite(LeftPwmPin, 0);
	softPwmWrite(RightPwmPin, 0);
}

	


