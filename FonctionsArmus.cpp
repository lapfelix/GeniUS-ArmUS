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
bool depart14 = false;
bool depart43 = false;
bool arret = false;
void detectionFrequence();


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
	//Variables
	bool estROBOT43; //ROBOT_43 part en premier!!
	bool premierSonEffectuer = false;


	THREAD thread_frequence;
	thread_frequence = THREAD_CreateSimple(detectionFrequence);
	thread_infrarouge = THREAD_CreateSimple(testInfrarouge);
	LCD_Printf("start program\n");
	while (arret!=true)
	{
		if (depart14==true)
			LCD_Printf("depart14\n");
		if (depart43==true)
			LCD_Printf("depart43\n");
	}
	LCD_ClearAndPrint("FINI");

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


//Fonctions
bool freq_watch()
{
	return DIGITALIO_Read(10);
}

//Sert à gérer le départ et l'arrêt du ou des programmes en fonction de la durée du 5kHz,
//La surveillance du signal se fait en temps réel et sans AUCUN MSLEEP !!!!
void detectionFrequence()
{


	//Vérifie quel est le ROBOT en cours!
	int estROBOT43 = DIGITALIO_Read(9);
	LCD_Printf("est robot43? %i", estROBOT43);

	bool etatFrequence = false;
	bool initTemps= false;
	bool premierSonEffectuer = false;
	int duree5khz=0;
	int temps = 0;
	//on choisit le bon mode de gestion d'erreur
	ERROR_SetMode(LCD_ONLY);

	while(1)
	{
		bool etatFrequence = freq_watch();



		//LCD_ClearAndPrint("valeur1=%d/n",duree5khz);
		if(etatFrequence==1 && initTemps == false)
		{
			initTemps = true;
			temps = SYSTEM_ReadTimerMSeconds();
			LCD_Printf("inittemps");
		}

		if (etatFrequence==0 && initTemps == true)
		{
			duree5khz=SYSTEM_ReadTimerMSeconds() - temps;
			initTemps = false;
			LCD_Printf("falldown");

			if (duree5khz < 2100 && duree5khz > 1900)
						{

							//Ecrire la fonction qui fait avancer le robot
							if(premierSonEffectuer == false)
							{
								if(estROBOT43 == false)
								{
									premierSonEffectuer = true;
									//partir le robot 14
									depart14 = true;
								}
								else
									premierSonEffectuer = true;

							}
							else if(premierSonEffectuer == true && estROBOT43 == true)
							{
								//partir le robot 43
								depart43=true;
							}
						}
			//duree5khz < 5500 &&
			else if (duree5khz > 4300 || (SYSTEM_ReadTimerMSeconds() - temps)>4000)
							{
								//Ecrire la fonction qui arrête les robots
								depart14 = false;
								depart43 = false;
								arret = true;
							}




				temps = 0;

			}


		}


	}




