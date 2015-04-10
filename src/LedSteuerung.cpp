	#include "LedSteuerung.hpp"


LedSteuerung::LedSteuerung(){
	wiringPiSetup();

	RedPwmValue = 0;
	GreenPwmValue = 0;
	BluePwmValue = 0;
	
	softPwmCreate(RedPwmPin, 0, RedPwmRange);
	softPwmCreate(GreenPwmPin, 0, GreenPwmRange);
	softPwmCreate(BluePwmPin, 0, BluePwmRange);
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

void LedSteuerung::increaseRedPwmValue(int newValue){
	if ((0 <= (RedPwmValue + newValue)) && ((RedPwmValue + NewValue) <= RedMaxPwmValue))
	{
		RedPwmvValue = RedPwmValue + newValue;
		this->writeRed;
	}
}

void LedSteuerung::increaseGreenPwmValue(int newValue){
	if ((0 <= (GreenPwmValue + newValue)) && ((GreenPwmValue + NewValue) <= GreenMaxPwmValue))
	{
		GreenPwmvValue = GreenPwmValue + newValue;
		this->writeGreen;
	}
}

void LedSteuerung::increaseBluePwmValue(int newValue){
	if ((0 <= (BluePwmValue + newValue)) && ((BluePwmValue + NewValue) <= BlueMaxPwmValue))
	{
		BluePwmvValue = BluePwmValue + newValue;
		this->writeBlue;
	}
}

void LedSteuerung::turnOff(void){
	RedPwmValue = 0;
	GreenPwmValue = 0;
	BluePwmValue = 0;

	this->writeRed();
	this->writeGreen();
	this->writeBlue();
}
	
void LedSteuerung::writeRed(void){
	if ((0 <= RedPwmValue) && (RedPwmValue <= RedMaxPwmValue))
	{	
		softPwmWrite(RedPwmPin, RedPwmValue);
	}	
}

void LedSteuerung::writeGreen(void){
	if ((0 <= GreenPwmValue) && (GreenPwmValue <= GreenMaxPwmValue))
	{	
		softPwmWrite(GreenPwmPin, GreenPwmValue);
	}	
}
	
void LedSteuerung::writeBlue(void){
	if ((0 <= BluePwmValue) && (BluePwmValue <= BlueMaxPwmValue))
	{	
		softPwmWrite(BluePwmPin, BluePwmValue);
	}	
}
	
	
LedSteuerung::~LedSteuerung(){
	softPwmWrite(RedPwmPin, 0);
	softPwmWrite(GreenPwmPin, 0);
	softPwmWrite(BluePwmPin, 0);
}

	


