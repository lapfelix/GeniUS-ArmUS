/*
 * main.cpp
 *
 *  Created on: 2014-11-09
 *      Author: DaeSoluS
 */
#include "Robot.h"
int main()
{
	bool laDerniereCarte = false;
	Robot unRobot(10);
	//unRobot.avancer(laDerniereCarte);
	//unRobot.tourner(90);
	while(1)
	{
		unRobot.lireNfc();
	}

	return 0;
}



