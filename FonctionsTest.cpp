/*
 * FonctionsTest.cpp
 *
 *  Created on: 2014-10-02
 *      Author: lusf1702
 */
#include <iostream>
#include <libarmus.h>
#include "Armus.h"
void setVitesseTEST(robot &unRobot,int &i,const short int TRANSITIONS)
{
	MOTOR_SetSpeed(MOTOR_RIGHT, 50);
	MOTOR_SetSpeed(MOTOR_LEFT, 50);
	THREAD_MSleep(500);

	//Distance parcourue en nombre de transitions effectués
	unRobot.encodeurDroit = ENCODER_Read(ENCODER_RIGHT);
	unRobot.encodeurGauche = ENCODER_Read(ENCODER_LEFT);
	//Affichage des encodeurs et des vitesses
	LCD_Printf("D: %i v: %i, G: %i v: %i \n",unRobot.encodeurDroit,50,unRobot.encodeurGauche,50);
}



