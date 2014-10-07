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
	const short int TRANSITIONS = 16;
	const short int MODE = 2; // TEST:0 PARCOURS:1 PID:2 

	int i = 1; //nb de cycle**

	robot unRobot;
	unRobot.vitesseGauche = 80;
	unRobot.vitesseDroit = 78;
	unRobot.distanceDroit = 0;
	unRobot.distanceGauche = 0;
	unRobot.totalDistanceDroit = 0;
	unRobot.totalDistanceGauche = 0;

	//variables à Pier-Luc bam d'un coup
	unRobot.distanceVoulue = 0; // distance supposément parcourue par le robot;
	unRobot.lecturevitesseDroite = 0;
	unRobot.lecturevitesseGauche = 0;
	unRobot.vitesseMoteurDroit = 0;
	unRobot.vitesseMoteurGauche = 0;
	unRobot.distanceMoteurDroit=0;
	unRobot.distanceMoteurGauche=0;

	int init;
	//Pour initialiser les compteurs avant le début, évite quelques bogues intermittants.
	init=ENCODER_Read(ENCODER_RIGHT);
	init=ENCODER_Read(ENCODER_LEFT);

    LCD_ClearAndPrint("New\n");

    	if(MODE == 0)
    	{
    	 while(true)
    	 {
    	    setVitesseTEST(unRobot,i,TRANSITIONS);
    	    i++;
    	 }
    	}
    	else if(MODE == 1)
    	{
    	    parcours(unRobot,i,TRANSITIONS);
    	}else if(MODE == 2)
    	{
    		int consigneVitesse = 10;//transitions / valeur de temps
    		
    	    while(1){
    	    		setVitesse(unRobot,i,consigneVitesse);
    	    }
    	}


    return 0;
}
