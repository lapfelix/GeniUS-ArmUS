/*
 * Programme Armus - Équipe P24
 * Création : 01/10/2014
 * Modifié  : 02/10/2014
 */

#include <iostream>
#include <libarmus.h>
#include "Armus.h"

void setVitesse(robot &unRobot,int &i,const short int TRANSITIONS)
{
	MOTOR_SetSpeed(MOTOR_RIGHT, unRobot.vitesseDroit);
    MOTOR_SetSpeed(MOTOR_LEFT, unRobot.vitesseGauche);
	THREAD_MSleep(1000);

	//Distance parcourue en nombre de transitions effectués
	unRobot.encodeurDroit = ENCODER_Read(ENCODER_RIGHT);
    unRobot.encodeurGauche = ENCODER_Read(ENCODER_LEFT);
    unRobot.totalDistanceDroit += unRobot.encodeurDroit;
    unRobot.totalDistanceGauche += unRobot.encodeurGauche;

	//Correction de la vitesse
	int valeurCompteurD = i * TRANSITIONS - unRobot.totalDistanceDroit;
    int valeurCompteurG = i * TRANSITIONS - unRobot.totalDistanceGauche;
    int valeurErreurD = TRANSITIONS - unRobot.encodeurDroit;
    int valeurErreurG = TRANSITIONS - unRobot.encodeurGauche;

	//Affichage des encodeurs et des vitesses
	LCD_Printf("D: %i v: %i, G: %i v: %i \n",unRobot.encodeurDroit,unRobot.vitesseDroit,unRobot.encodeurGauche,unRobot.vitesseGauche);


	//correction entre entre les 2 encodeurs
	int correcteurDroit = (unRobot.encodeurDroit - unRobot.encodeurGauche) > 0 ? 0 :
						   unRobot.encodeurGauche - unRobot.encodeurDroit  ;


	int correcteurGauche = (unRobot.encodeurGauche - unRobot.encodeurDroit) > 0 ? 0 :
							 unRobot.encodeurDroit - unRobot.encodeurGauche;


	//Formules d'ajustement des moteurs
    unRobot.vitesseDroit+= (int)0.108 * valeurCompteurD + valeurErreurD * 0.27 + correcteurDroit *0.5 ;
    unRobot.vitesseGauche+= (int)0.108 * valeurCompteurG + valeurErreurG * 0.27 + correcteurGauche*0.5;
}

//Retourne la distance parcourue en cm
/*
int distance(robot unRobot&)
{
	return 0;
}
*/

