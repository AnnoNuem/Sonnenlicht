#ifndef __LedSteuerung__hpp___
#define ___LedSteuerung__hpp__

#include <wiringPi.h>
#include <curses.h>
#include <softPwm.h>
#include <unistd.h>
#include <math.h>

class LedSteuerung{
	private:

	const static int LeftForwardPin = 2;
	const static int LeftBackwardPin = 3;
	const static int LeftPwmPin = 0;

	const static int RightForwardPin = 8;
	const static int RightBackwardPin = 9;
	const static int RightPwmPin = 7;

	const static int LeftPwmRange = 100;
	const static int RightPwmRange = 100;
	
	const static int acceleration = 5;
	const static int brakeForce = 5;

	const static int steeringAngle = 10;

	const static int deltaSpeed = 1;

	int LeftSpeed;
	int RightSpeed;
	bool forward;
	
	LedSteuerung();
	
	LedSteuerung(const LedSteuerung&);

	LedSteuerung& operator= (const LedSteuerung&);

	public:
	static LedSteuerung& instance()
	{
		static LedSteuerung _instance;
		return _instance;
	}

	~LedSteuerung();
	
	void setSpeed(int speed);
	void setLeftSpeed(int speed);
	void setRightSpeed(int speed);
	void faster(void);
	void slower(void);
	void left(void);
	void right(void);
	void stop(void);
	void straight(void);
	void changeDirection(void);
	void changeDirectionLeft(void);
	void changeDirectionRight(void);
	void writeOut(void);
};
#endif

