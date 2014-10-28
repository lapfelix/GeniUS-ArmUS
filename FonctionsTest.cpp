/*
 * FonctionsTest.cpp
 *
 *  Created on: 2014-10-02
 *      Author: lusf1702
 */

#include "Armus.h"
#include <iostream>
#include <fstream>
void parcoursTest(robot &unRobot, short int TRANSITIONS)
{
	/*
	reinitialiser(unRobot);
	encodeurDroitTest();
	reinitialiser(unRobot);
	encodeurGaucheTest();
	*/

	//boucle permettant de garder le programme en execution pour etre capable d'arreter son execution en pesant le bouton 'user'
	while(1)
	{
		MOTOR_SetSpeed(MOTOR_RIGHT, 40);
		MOTOR_SetSpeed(MOTOR_LEFT, 40);
		THREAD_MSleep(1000);
	}
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

void testCouleur()
{
	//TODO: un 'if' qui prend la couleur avec le i2c ou analogue dependant du robot

	//le robot 43 a une pin entre le digital 9 et le Vcc
	bool estRobot43 = (DIGITALIO_Read(9) == 1);

	//initialiser le capteur cest important quand on s'appelle robot 43
	if(estRobot43)
		initCapteurI2C();
	ofstream fichier;
	fichier.open("couleur.txt");
	while(1)
	{
		RgbColor readColor;
		//step 1
		if(estRobot43)
			readColor = getColorI2C();
		else
			readColor = getColorAnalog();
		LCD_Printf("\nR=%i, G=%i, B=%i", readColor.r, readColor.g, readColor.b);
		fichier << "background-color: rgb(" <<readColor.r<<","<<readColor.g<<","<<readColor.b<<")"<< endl;
		//step 2
        HsbColor colorsHSB = RGBtoHSB(readColor);
		//LCD_Printf(" H=%.4f, S=%.4f, B=%.4f ", colorsHSB.hue, colorsHSB.saturation, colorsHSB.brightness);

		string laCouleur;
		/*if(estRobot43)
			laCouleur = currentFloorColor(colorsHSB);*/
		//else
			//laCouleur = currentFloorColorAnalog(colorsHSB);
		//LCD_Printf("%s",laCouleur.c_str());
	}
}



THREAD thread_infrarouge;
void testInfrarouge()
{

	LCD_ClearAndPrint("Test Infrarouge\n");

		int sortie = 0;
		sortie = IR_Detect(IR_FRONT);
		switch(sortie)
		{
			case 0: LCD_Printf("RIEN\n");break;
			case 1: LCD_Printf("DROITE\n");break;
			case 2: LCD_Printf("GAUCHE\n");break;
			case 3: LCD_Printf("DROITE ET GAUCHE\n");break;
		}
		THREAD_MSleep(100);
}



