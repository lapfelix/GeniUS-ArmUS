/*
 * FonctionsTest.cpp
 *
 *  Created on: 2014-10-02
 *      Author: lusf1702
 */
#include <iostream>
#include <libarmus.h>
#include "Armus.h"


void parcoursTest(robot &unRobot, short int TRANSITIONS)
{
	reinitialiser(unRobot);
	encodeurDroitTest();
	reinitialiser(unRobot);
	encodeurGaucheTest();
	//vitesseTEST(unRobot,TRANSITIONS);
}



void vitesseTEST(robot &unRobot,short int TRANSITIONS)
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

void encodeurDroitTest()
{
	MOTOR_SetSpeed(8,30);
	THREAD_MSleep(100);
	short int encodeurDroit = 0;
	while(encodeurDroit <= 64)
	{
		encodeurDroit+=ENCODER_Read(ENCODER_RIGHT);
		LCD_Printf("D: %i \n",encodeurDroit);
	}
	MOTOR_SetSpeed(8,0);
}

void encodeurGaucheTest()
{
	MOTOR_SetSpeed(7,30);
	THREAD_MSleep(100);
	short int encodeurGauche = 0;
	while(encodeurGauche <= 64)
	{
		encodeurGauche += ENCODER_Read(ENCODER_LEFT);
		LCD_Printf("G: %i \n",encodeurGauche);
	}
	MOTOR_SetSpeed(7,0);
}



