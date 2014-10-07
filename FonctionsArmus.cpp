/*
 *  * Programme Armus - Équipe P24
 * Création : 01/10/2014
 * Modifié  : 02/10/2014
 */

#include <iostream>
#include <libarmus.h>
#include "Armus.h"

const int VITESSE_INITIALE_7 = 80;
const int VITESSE_INITIALE_8 = 78;
const int TEMPS = 100;//msecondes

const float FC_VITESSE = 1;//facteur de correction de la vitesse
const float FC_DISTANCE = 0.5;//facteur de correction de la distance


void setVitesse(robot &unRobot,int &i,const short int consigneVitesse)
{

	//Distance parcourue en nombre de transitions effectuees
	unRobot.encodeurDroit = ENCODER_Read(ENCODER_RIGHT);
    unRobot.encodeurGauche = ENCODER_Read(ENCODER_LEFT);
    unRobot.totalDistanceDroit += unRobot.encodeurDroit;
    unRobot.totalDistanceGauche += unRobot.encodeurGauche;


	THREAD_MSleep(TEMPS);

	unRobot.lecturevitesseDroite = ENCODER_Read(ENCODER_RIGHT);
	unRobot.lecturevitesseGauche = ENCODER_Read(ENCODER_LEFT);
	unRobot.distanceVoulue = unRobot.distanceVoulue+unRobot.consigneVitesse;
	unRobot.distanceMoteurDroit = unRobot.distanceMoteurDroit+unRobot.lecturevitesseDroite;
	unRobot.distanceMoteurGauche = unRobot.distanceMoteurGauche + unRobot.lecturevitesseGauche;


	unRobot.vitesseMoteurDroit = -FC_VITESSE*(unRobot.lecturevitesseDroite-unRobot.consigneVitesse)-FC_DISTANCE*(unRobot.distanceMoteurDroit-unRobot.distanceVoulue);
	unRobot.vitesseMoteurGauche = -FC_VITESSE*(unRobot.lecturevitesseGauche-unRobot.consigneVitesse)-FC_DISTANCE*(unRobot.distanceMoteurGauche-unRobot.distanceVoulue);
	LCD_Printf(",EG %d, ED %d\n ", unRobot.lecturevitesseGauche-unRobot.consigneVitesse, unRobot.lecturevitesseDroite-unRobot.consigneVitesse);



	MOTOR_SetSpeed(7,unRobot.vitesseMoteurGauche);
	MOTOR_SetSpeed(8,unRobot.vitesseMoteurDroit);

}



void parcours(robot &unRobot,int &i,const short int TRANSITIONS)
{
	//1ere partie, avancer de 222.5cm
	cmToRevolution(222,unRobot,i,TRANSITIONS); //(200 + 45/2)cm


	//2e partie, tourner de -90degrees
	//setAngle(-90,unRobot,i,TRANSITIONS);
	/*
	//3e partie, avancer de 47.5cm
	cmToRevolution(47.5,unRobot,i,TRANSITIONS); //(50/2 + 45/2)cm

	//4e partie, tourner de 90degrees
	setAngle(90,unRobot,i,TRANSITIONS);

	//3e partie, avancer de 47.5cm
	cmToRevolution(47.5,unRobot,i,TRANSITIONS); //(50/2 + 45/2)cm

	//5e partie, tourner de 90degrees
	setAngle(90,unRobot,i,TRANSITIONS);

	//6e partie, avancer de 47.5cm
	cmToRevolution(47.5,unRobot,i,TRANSITIONS); //(50/2 + 45/2)cm

	//7e partie, tourner de -90degrees
	setAngle(-90,unRobot,i,TRANSITIONS);

	//8e partie, avancer de 18cm
	cmToRevolution(18,unRobot,i,TRANSITIONS);

	//9e partie, tourner de 45degrees
	setAngle(45,unRobot,i,TRANSITIONS); //(180-135)degrees

	//10e partie, avancer de 30cm
	cmToRevolution(30,unRobot,i,TRANSITIONS); //(60/2)cm

	//11e partie, tourner de -90degrees
	setAngle(-90,unRobot,i,TRANSITIONS);

	//12e partie, avancer de 82.5cm
	cmToRevolution(82.5,unRobot,i,TRANSITIONS); //(60 + 45/2)cm

	//13e partie, tourner de 45degrees
	setAngle(45,unRobot,i,TRANSITIONS); //(180-135)degrees

	//14e partie, avancer de 32cm
	cmToRevolution(32,unRobot,i,TRANSITIONS); //(60 + 45/2)cm

	//13e partie, tourner de 22.5degrees
	setAngle(22.5,unRobot,i,TRANSITIONS); //(180 - 90 - 67.5)degrees

	//last sprint!
	cmToRevolution(100,unRobot,i,TRANSITIONS);

*/
}

void cmToRevolution(int distanceCm,robot &unRobot,int &i,const short int TRANSITIONS)
{

	unRobot.vitesseGauche =80;
	unRobot.vitesseDroit = 78;

	int transitions = distanceCm * 2.65; // cm * 64/(7.7*pi)


	while((unRobot.totalDistanceGauche+unRobot.totalDistanceDroit)/2<=transitions)
	{
		setVitesse(unRobot,i,TRANSITIONS);
	}


	//Affichage
	//LCD_Printf("Cible: %i Moyenne : %i\n",transitions,(unRobot.totalDistanceGauche+unRobot.totalDistanceDroit / 2));
	//LCD_Printf("Gauche: %i Droit: %i\n",unRobot.totalDistanceGauche,unRobot.totalDistanceDroit);


	MOTOR_SetSpeed(MOTOR_RIGHT, 0);
    MOTOR_SetSpeed(MOTOR_LEFT, 0);

	unRobot.totalDistanceGauche = 0;
	unRobot.totalDistanceDroit = 0;
	i=0;
}

void setAngle(int angle,robot &unRobot,int &i,const short int TRANSITIONS)
{
	THREAD_MSleep(500);
	int transitions =  (angle * 22 / 90) * 2.65 - 15;
	LCD_Printf("FUCKKK , %i", transitions);
	if(angle<0)
	{
		//Avancer la roue droite
		unRobot.vitesseGauche =0;
		unRobot.vitesseDroit = 30;

		do
		{

			setVitesse(unRobot,i,TRANSITIONS);
		}
		while((unRobot.totalDistanceDroit)<= 0 - transitions);
		LCD_Printf("\nAAhhh , %i", unRobot.totalDistanceDroit);
	}
	else
	{
		//Avancer la roue gauche
		unRobot.vitesseGauche =52;
		unRobot.vitesseDroit = 0;

		do
		{
			LCD_Printf("RRRRRRRRRRRRRHHHH");
			setVitesse(unRobot,i,TRANSITIONS);
		}
		while((unRobot.totalDistanceGauche)<=transitions);

	}

	MOTOR_SetSpeed(MOTOR_RIGHT, 0);
    MOTOR_SetSpeed(MOTOR_LEFT, 0);

	unRobot.totalDistanceGauche = 0;
	unRobot.totalDistanceDroit = 0;
	i=0;
}


//Retourne la distance parcourue en cm
/*
int distance(robot unRobot&)
{
	return 0;
}
*/
