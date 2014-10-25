/*
 *  * Programme Armus - Équipe P24
 * Création : 01/10/2014
 * Modifié  : 02/10/2014
 */

#include <iostream>
#include <math.h>
#include <libarmus.h>
#include "Armus.h"

const int TEMPS = 250;//msecondes
const float FC_VITESSE = 1;//facteur de correction de la vitesse
const float FC_DISTANCE = 0.5;//facteur de correction de la distance

void vitesse(robot &unRobot,short int transitionsGauche,short int transitionsDroite)
{
	THREAD_MSleep(TEMPS);
	unRobot.lecturevitesseDroite = ENCODER_Read(ENCODER_RIGHT);
	unRobot.lecturevitesseGauche = ENCODER_Read(ENCODER_LEFT);
	unRobot.distanceVoulueGauche += transitionsGauche;
	unRobot.distanceVoulueDroite += transitionsDroite;
	unRobot.distanceMoteurDroit += unRobot.lecturevitesseDroite;
	unRobot.distanceMoteurGauche += unRobot.lecturevitesseGauche;


	int correctionGauche = 0;
	int correctionDroit = 0;

	unRobot.vitesseMoteurDroit = (int)(-FC_VITESSE*(float)(unRobot.lecturevitesseDroite-transitionsDroite)-FC_DISTANCE*(float)(unRobot.distanceMoteurDroit-unRobot.distanceVoulueDroite));
	unRobot.vitesseMoteurGauche = (int)(-FC_VITESSE*(float)(unRobot.lecturevitesseGauche-transitionsGauche)-FC_DISTANCE*(float)(unRobot.distanceMoteurGauche-unRobot.distanceVoulueGauche));
//	unRobot.vitesseMoteurGauche = (int)(-FC_VITESSE*(float)(unRobot.lecturevitesseGauche-transitionsGauche)-FC_DISTANCE*(float)(unRobot.distanceMoteurGauche-unRobot.distanceVoulueGauche));

	MOTOR_SetSpeed(7,unRobot.vitesseMoteurGauche);
	MOTOR_SetSpeed(8,unRobot.vitesseMoteurDroit);
}

void parcours(robot &unRobot, short int TRANSITIONS)
{

		//1ere partie, avancer de 222.5cm
		reinitialiser(unRobot);
		avancer(242.5,unRobot,TRANSITIONS,TRANSITIONS); //(200 + 45/2)cm

		//2e partie, tourner de -90degrees
		reinitialiser(unRobot);
		tourner(90, unRobot, false);

		//3e partie, avancer de 47.5cm
		reinitialiser(unRobot);
		avancer(30.5,unRobot,TRANSITIONS,TRANSITIONS); //(50/2 + 45/2)cm

		//4e partie, tourner de 90degrees
		reinitialiser(unRobot);
		tourner(90, unRobot, true);

		//5e partie, avancer de 47.5cm
		reinitialiser(unRobot);
		avancer(30,unRobot,TRANSITIONS,TRANSITIONS); //(50/2 + 45/2)cm

		//6e partie, tourner de 90degrees
		reinitialiser(unRobot);
		tourner(90, unRobot, true);

		//7e partie, avancer de 47.5cm
		reinitialiser(unRobot);
		avancer(47.5,unRobot,TRANSITIONS,TRANSITIONS); //(50/2 + 45/2)cm

		//8e partie, tourner de -90degrees
		reinitialiser(unRobot);
		tourner(83, unRobot, false);

		//9e partie, avancer de 18cm
		reinitialiser(unRobot);
		avancer(18,unRobot,TRANSITIONS,TRANSITIONS);

		//10e partie, tourner de 45degrees
		reinitialiser(unRobot);
		tourner(45, unRobot, true); //(180-135)degrees

		//11e partie, avancer de 30cm
		reinitialiser(unRobot);
		avancer(30,unRobot,TRANSITIONS,TRANSITIONS); //(60/2)cm

		//12e partie, tourner de -90degrees
		reinitialiser(unRobot);
		tourner(87, unRobot, false);

		//13e partie, avancer de 82.5cm
		reinitialiser(unRobot);
		avancer(60,unRobot,TRANSITIONS,TRANSITIONS); //(60 + 45/2)cm

		reinitialiser(unRobot);
		//14e partie, tourner de 45degrees
		tourner(40, unRobot, true);//(180-135)degrees

		//15e partie, avancer de 32cm
		reinitialiser(unRobot);
		avancer(32,unRobot,TRANSITIONS,TRANSITIONS); //(60 + 45/2)cm

		//15e partie, tourner 5 degres a droite
		reinitialiser(unRobot);
		tourner(15, unRobot, true); //(60 + 45/2)cm

		//last sprint!
		reinitialiser(unRobot);
		avancer(120,unRobot,TRANSITIONS,TRANSITIONS);
		reinitialiser(unRobot);
/*

	reinitialiser(unRobot);
	tourner(90,unRobot,true);
	reinitialiser(unRobot);
	tourner(90,unRobot,false);
	reinitialiser(unRobot);
	tourner(180,unRobot,true);
	reinitialiser(unRobot);
	tourner(180,unRobot,false);
	reinitialiser(unRobot);
	tourner(360,unRobot,true);
	reinitialiser(unRobot);
	tourner(360,unRobot,false);

	*/
	//reinitialiser(unRobot);
	//tourner(180,unRobot,false);
	//reinitialiser(unRobot);
		//arrete les moteurs
		unRobot.vitesseMoteurDroit = 0;
		unRobot.vitesseMoteurGauche = 0;
		MOTOR_SetSpeed(7,unRobot.vitesseMoteurGauche);
		MOTOR_SetSpeed(8,unRobot.vitesseMoteurDroit);
}

void avancer(int distanceCm,robot &unRobot,short int transitionGauche, short int transitionDroite)
{

	unRobot.vitesseMoteurDroit = 30;
	unRobot.vitesseMoteurGauche = 30;

	float nbTransitions = distanceCm / 0.43;
	while((unRobot.distanceMoteurGauche+unRobot.distanceMoteurDroit)/2<=nbTransitions)
	{
		int moyenneDistance = (unRobot.distanceMoteurGauche+unRobot.distanceMoteurDroit)/2;
		LCD_Printf("%i \n",moyenneDistance);
		//if(moyenneDistance >= nbTransitions*0.75)
		//{
		//	vitesse(unRobot,5,5);
		//}
		//else
		//{
			vitesse(unRobot,10,10);
		//}
	}
	LCD_Printf("STOP \n");
}

void tourner(int angle, robot &unRobot, bool tourneGauche){
	float tourCompletCm = 1.604;//((13.5 * M_PI))*2.42222;

	int init;
	//Pour initialiser les compteurs avant le début, évite quelques bogues intermittants.
	init=ENCODER_Read(ENCODER_RIGHT);
	init=ENCODER_Read(ENCODER_LEFT);

	if(tourneGauche)
	{
		unRobot.distanceMoteurGauche = 0;
		while(unRobot.distanceMoteurGauche <= (int)((angle - 15)/tourCompletCm))
		{
			unRobot.distanceMoteurGauche += ENCODER_Read(ENCODER_LEFT);
			MOTOR_SetSpeed(MOTOR_LEFT,35);
			MOTOR_SetSpeed(MOTOR_RIGHT,0);
			//LCD_Printf("lol %i vs %f\n",(int)((tourCompletCm *((float)angle/360.f)*2.9)),((tourCompletCm *((float)angle/360.f)*2.9)));
			//vitesse(unRobot,5,0);
		}
	}
	else
	{
		unRobot.distanceMoteurDroit = 0;
				while(unRobot.distanceMoteurDroit <= (int)((angle - 15)/tourCompletCm))
				{
					unRobot.distanceMoteurDroit += ENCODER_Read(ENCODER_RIGHT);
					MOTOR_SetSpeed(MOTOR_LEFT,0);
					MOTOR_SetSpeed(MOTOR_RIGHT,35);
		}
	}
}


void reinitialiser(robot &unRobot)
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
	//MOTOR_SetSpeed(7,unRobot.vitesseMoteurGauche);
	//MOTOR_SetSpeed(8,unRobot.vitesseMoteurDroit);
}
