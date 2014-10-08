<<<<<<< HEAD
/*
============================================================================
 Name : Armus.cpp
 Author :Pier-Luc
 Version :10.0
 Description : Hello world - Exe source file
============================================================================
*/

// Include Files

#include <libarmus.h>

// Global Functions
const int TEMPS = 100;//msecondes
const float FC_VITESSE = 1;//facteur de correction de la vitesse
const float FC_DISTANCE = 0.5;//facteur de correction de la distance

int main()
{
	int consigneVitesse = 10;//transitions / valeur de temps
	int distanceVoulue = 0; // distance supposément parcourue par le robot;
	int init = ENCODER_Read(ENCODER_RIGHT);
	init = ENCODER_Read(ENCODER_LEFT);
	int lecturevitesseDroite = 0;
	int lecturevitesseGauche = 0;
	int vitesseMoteurDroit = 0;
	int vitesseMoteurGauche = 0;
	int distanceMoteurDroit=0;
	int distanceMoteurGauche=0;

	while(1)
	{
	THREAD_MSleep(TEMPS);
	lecturevitesseDroite = ENCODER_Read(ENCODER_RIGHT);
	lecturevitesseGauche = ENCODER_Read(ENCODER_LEFT);
	distanceVoulue= distanceVoulue+consigneVitesse;
	distanceMoteurDroit = distanceMoteurDroit+lecturevitesseDroite;
	distanceMoteurGauche = distanceMoteurGauche + lecturevitesseGauche;


	vitesseMoteurDroit = -FC_VITESSE*(lecturevitesseDroite-consigneVitesse)-FC_DISTANCE*(distanceMoteurDroit-distanceVoulue);
	vitesseMoteurGauche = -FC_VITESSE*(lecturevitesseGauche-consigneVitesse)-FC_DISTANCE*(distanceMoteurGauche-distanceVoulue);
	LCD_Printf(",EG %d, ED %d\n ", lecturevitesseGauche-consigneVitesse, lecturevitesseDroite-consigneVitesse);



	MOTOR_SetSpeed(7,vitesseMoteurGauche);
	MOTOR_SetSpeed(8,vitesseMoteurDroit);

//allo



	}

	return 0;
}
=======
/*
 * Programme Armus - Equipe P24
 * Creation : 01/10/2014
 * Modifie  : 04/10/2014
 */
#include <iostream>
#include <libarmus.h>
#include <cmath>
#include "Armus.h"


int main()
{
const short int TRANSITIONS = 10;
const short int MODE = 1; // TEST:0 PARCOURS:1 PID:2

int i = 1; //nb de cycle**

robot unRobot;
resetValues(unRobot);





    LCD_ClearAndPrint("New 1\n");

    if(MODE == 0)
    {
		while(true)
		{
		   //setVitesseTEST(unRobot,i,TRANSITIONS);
		   i++;
		}
    }
    else if(MODE == 1)
    {
       parcours(unRobot,TRANSITIONS);
    }
    else if(MODE == 2)
    {
    	const short int consigneVitesse = 10;//transitions / valeur de temps

    	while(1)
    	{
    		setVitesse(unRobot,i,consigneVitesse);
    	}
    }



    return 0;
}
>>>>>>> MergeModifsPierLuc
