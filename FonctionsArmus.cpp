/*
 *  * Programme Armus - Équipe P24
 * Création : 01/10/2014
 * Modifié  : 02/10/2014
 */

#include <iostream>
#include <math.h>
#include <libarmus.h>
#include "Armus.h"


const int TEMPS = 100;//msecondes

const float FC_VITESSE = 1;//facteur de correction de la vitesse
const float FC_DISTANCE = 0.5;//facteur de correction de la distance


void setVitesse(robot &unRobot,short int transitionsGauche,short int transitionsDroite)
{
	THREAD_MSleep(TEMPS);

	unRobot.lecturevitesseDroite = ENCODER_Read(ENCODER_RIGHT);
	unRobot.lecturevitesseGauche = ENCODER_Read(ENCODER_LEFT);
	unRobot.distanceVoulueGauche += transitionsGauche;
	unRobot.distanceVoulueDroite += transitionsDroite;
	unRobot.distanceMoteurDroit += unRobot.lecturevitesseDroite;
	unRobot.distanceMoteurGauche += unRobot.lecturevitesseGauche;

	unRobot.vitesseMoteurDroit = -FC_VITESSE*(unRobot.lecturevitesseDroite-transitionsDroite)-FC_DISTANCE*(unRobot.distanceMoteurDroit-unRobot.distanceVoulueDroite);
	unRobot.vitesseMoteurGauche = -FC_VITESSE*(unRobot.lecturevitesseGauche-transitionsGauche)-FC_DISTANCE*(unRobot.distanceMoteurGauche-unRobot.distanceVoulueGauche);

	MOTOR_SetSpeed(7,unRobot.vitesseMoteurGauche);
	MOTOR_SetSpeed(8,unRobot.vitesseMoteurDroit);

}



void parcours(robot &unRobot, short int TRANSITIONS)
{
	//1ere partie, avancer de 222.5cm
	resetValues(unRobot);
	cmToRevolution(225,unRobot,TRANSITIONS,TRANSITIONS); //(200 + 45/2)cm

	//2e partie, tourner de -90degrees
	resetValues(unRobot);
	turn(90, unRobot, false);

	//3e partie, avancer de 47.5cm
	resetValues(unRobot);
	cmToRevolution(48,unRobot,TRANSITIONS,TRANSITIONS); //(50/2 + 45/2)cm

	//4e partie, tourner de 90degrees
	resetValues(unRobot);
	turn(90, unRobot, true);

	//3e partie, avancer de 47.5cm
	resetValues(unRobot);
	cmToRevolution(48,unRobot,TRANSITIONS,TRANSITIONS); //(50/2 + 45/2)cm

	//5e partie, tourner de 90degrees
	resetValues(unRobot);
	turn(90, unRobot, true);

	//6e partie, avancer de 47.5cm
	resetValues(unRobot);
	cmToRevolution(48,unRobot,TRANSITIONS,TRANSITIONS); //(50/2 + 45/2)cm

	//7e partie, tourner de -90degrees
	resetValues(unRobot);
	turn(90, unRobot, false);

	//8e partie, avancer de 18cm
	resetValues(unRobot);
	cmToRevolution(18,unRobot,TRANSITIONS,TRANSITIONS);

	//9e partie, tourner de 45degrees
	resetValues(unRobot);
	turn(45, unRobot, true); //(180-135)degrees

	//10e partie, avancer de 30cm
	resetValues(unRobot);
	cmToRevolution(30,unRobot,TRANSITIONS,TRANSITIONS); //(60/2)cm

	//11e partie, tourner de -90degrees
	resetValues(unRobot);
	turn(90, unRobot, false);

	//12e partie, avancer de 82.5cm
	resetValues(unRobot);
	cmToRevolution(82.5,unRobot,TRANSITIONS,TRANSITIONS); //(60 + 45/2)cm

	resetValues(unRobot);
	//13e partie, tourner de 45degrees
	turn(45, unRobot, true);//(180-135)degrees

	//14e partie, avancer de 32cm
	resetValues(unRobot);
	cmToRevolution(32,unRobot,TRANSITIONS,TRANSITIONS); //(60 + 45/2)cm

	//13e partie, tourner de 22.5degrees
	resetValues(unRobot);
	turn(23, unRobot, true); //(180 - 90 - 67.5)degrees

	//last sprint!
	resetValues(unRobot);
	cmToRevolution(100,unRobot,TRANSITIONS,TRANSITIONS);


}

void cmToRevolution(int distanceCm,robot &unRobot,short int transitionGauche, short int transitionDroite)
{

	float nbTransitions = distanceCm / 0.45;

	while((unRobot.distanceMoteurGauche+unRobot.distanceMoteurDroit)/2<=nbTransitions)
	{
		int moyenneDistance = (unRobot.distanceMoteurGauche+unRobot.distanceMoteurDroit)/2;
		if(moyenneDistance >= nbTransitions*0.75)
		{
			LCD_Printf("Je rentre");
			setVitesse(unRobot,5,5);
		}
		else
		{
			setVitesse(unRobot,10,10);
		}

		//LCD_Printf("FUCKK , %i %f\n", (unRobot.distanceMoteurGauche+unRobot.distanceMoteurDroit)/2,nbTransitions);
	}

}

void turn(int angle, robot &unRobot, bool tourneGauche){
	float tourCompletCm = (14.5 * M_PI);

	if(tourneGauche)
	{
		while(unRobot.distanceMoteurGauche <= (int)((tourCompletCm *((float)angle/360.f)*4)))
		{
			setVitesse(unRobot,10,0);
			//LCD_Printf("Arg1 %i, Arg2 %i\n ", unRobot.distanceMoteurGauche, (int)((tourCompletCm *((float)angle/360.f)*2.22222)));

		}
	}
	else
	{
		//avance le moteur droit
		while(unRobot.distanceMoteurDroit <=(int)((tourCompletCm *((float)angle/360.f)*4)))
					setVitesse(unRobot,0,10);
	}
}

void resetValues(robot &unRobot)
{
	THREAD_MSleep(400);
	int init;
	//Pour initialiser les compteurs avant le début, évite quelques bogues intermittants.
	init=ENCODER_Read(ENCODER_RIGHT);
	init=ENCODER_Read(ENCODER_LEFT);
	//variables a Pier-Luc bam d'un coup
	unRobot.distanceVoulueGauche = 0;
	unRobot.distanceVoulueDroite = 0; // distance supposément parcourue par le robot;
	unRobot.lecturevitesseDroite = 0;
	unRobot.lecturevitesseGauche = 0;
	unRobot.vitesseMoteurDroit = 0;
	unRobot.vitesseMoteurGauche = 0;
	unRobot.distanceMoteurDroit=0;
	unRobot.distanceMoteurGauche=0;
}


