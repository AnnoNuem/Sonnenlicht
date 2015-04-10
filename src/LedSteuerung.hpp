#ifndef __LedSteuerung__hpp___
#define ___LedSteuerung__hpp__

#include <wiringPi.h>
#include <curses.h>
#include <softPwm.h>
#include <unistd.h>
#include <math.h>

class LedSteuerung{
	private:

	const static int RedPwmPin = 0;
	const static int GreenPwmPin = 7;
	const static int BluePwmPin = 7;

	const static int RedPwmRange = 1000;
	const static int GreenPwmRange = 1000;
	const static int BluePwmRange = 1000;

	int RedPwmValue;
	int GreenPwmValue;
	int BluePwmValue;
	
	LedSteuerung();
	
	LedSteuerung(const LedSteuerung&);

	LedSteuerung& operator= (const LedSteuerung&);

	void writeRed(void);
	void writeGreen(void);
	void writeBlue(void);

	public:

	static int RedMaxPwmValue = 100;
	static int GreenMaxPwmValue = 100;
	static int BlueMaxPwmValue = 100;

	static LedSteuerung& instance()
	{
		static LedSteuerung _instance;
		return _instance;
	}

	~LedSteuerung();
	
	void setRedPwmValue(int newValue);
	void setGreenPwmValue(int newValue);
	void setBluePwmValue(int newValue);
	void setBrightness(int newValue);

	void increaseBrightness(int newValue);
	void increaseRedPwmValue(int newValue);
	void increaseGreenPwmValue(int newValue);
	void increaseBluePwmValue(int newValue);

	void turnOff(void);

	int getRedPwmValue(void);
	int getGreenPwmValue(void);
	int getBluePwmValue(void);

};
#endif

