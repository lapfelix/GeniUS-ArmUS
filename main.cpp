/*
 * main.cpp
 *
 *  Created on: 2014-11-09
 *      Author: DaeSoluS
 */
#include "Robot.h"
#include <libarmus.h>

int main()
{
	bool laDerniereCarte = false;
	Robot unRobot(10);
	AUDIO_SetVolume(80);
	unsigned int music, state = 0;

	while(1)
	{
		unRobot.lireNfc();
	}

	return 0;
}
