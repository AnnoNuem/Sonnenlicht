#include "LedSteuerung.hpp"
#include <curses.h>
#include <iostream>
#include <sys/ioctl.h>
#include <sys/time.h>
#include <sys/types.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>

#define NAME_LENGTH 128
	
LedSteuerung& l = LedSteuerung::instance();

int main(int argc, const char* argv[]){
	int ch;
	
	// input keys
	const char keyIncreaseRed = 'q';
	const char keyDecreaseRed = 'a';
	const char keyIncreaseGreen = 'w';
	const char keyDecreaseGreen = 's';
	const char keyIncreaseBlue = 'e';
	const char keyDecreaseBlue = 'd';

	const int delta = 10;

	initscr();
	noecho();
	nonl();
	timeout(0);
	keypad(stdscr, TRUE);

	do
	{
		ch = getch();
		clear();
		printw("R: %d, G: %d, B: %d", l.getRedPwmValue(), l.getGreenPwmValue(), l.getBluePwmValue());

		switch(ch){
			case keyIncreaseRed: l.increaseRedPwmValue(delta); break;
			case keyDecreaseRed: l.increaseRedPwmValue(-delta); break;
			case keyIncreaseGreen: l.increaseGreenPwmValue(delta); break;
			case keyDecreaseGreen: l.increaseGreenPwmValue(-delta); break;
			case keyIncreaseBlue: l.increaseBluePwmValue(delta); break;
			case keyDecreaseBlue: l.increaseBluePwmValue(-delta); break;
		}
	}while( ch != 'x');
	clear();
	endwin();
	return 0;
}
