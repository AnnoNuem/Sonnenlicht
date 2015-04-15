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

void LedSteuerung::setRedPwmValue(int newValue){
	if ((0 <= newValue) && (newValue <= RedMaxPwmValue))
	{
		RedPwmValue = newValue;
	}
}

void LedSteuerung::setGreenPwmValue(int newValue){
	if ((0 <= newValue) && (newValue <= GreenMaxPwmValue))
	{
		GreenPwmValue = newValue;
	}
}

void LedSteuerung::setBluePwmValue(int newValue){
	if ((0 <= newValue) && (newValue <= BlueMaxPwmValue))
	{
		BluePwmValue = newValue;
	}
}

void LedSteuerung::setBrightness(int newValue){
	this->setRedPwmValue(newValue);
	this->setGreenPwmValue(newValue);
	this->setBluePwmValue(newValue);
}

void LedSteuerung::increaseBrightness(int newValue){
	this->increaseRedPwmValue(newValue);
	this->increaseGreenPwmValue(newValue);
	this->increaseBluePwmValue(newValue);
}

void LedSteuerung::increaseRedPwmValue(int newValue){
	if ((0 <= (RedPwmValue + newValue)) && ((RedPwmValue + newValue) <= RedMaxPwmValue))
	{
		this->RedPwmValue = this->RedPwmValue + newValue;
		this->writeRed();
	}
}

void LedSteuerung::increaseGreenPwmValue(int newValue){
	if ((0 <= (GreenPwmValue + newValue)) && ((GreenPwmValue + newValue) <= GreenMaxPwmValue))
	{
		this->GreenPwmValue = this->GreenPwmValue + newValue;
		this->writeGreen();
	}
}

void LedSteuerung::increaseBluePwmValue(int newValue){
	if ((0 <= (BluePwmValue + newValue)) && ((BluePwmValue + newValue) <= BlueMaxPwmValue))
	{
		this->BluePwmValue = BluePwmValue + newValue;
		this->writeBlue();
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

int LedSteuerung::getRedPwmValue(void){
	return RedPwmValue;
}

int LedSteuerung::getGreenPwmValue(void){
	return GreenPwmValue;
}

int LedSteuerung::getBluePwmValue(void){
	return BluePwmValue;
}
	


