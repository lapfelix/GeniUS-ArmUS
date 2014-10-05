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
	const short int MODE = 1; // TEST:0 DEV:1

	int i = 1; //nb de cycle**

	robot unRobot;
	unRobot.vitesseGauche = 80;
	unRobot.vitesseDroit = 78;
	unRobot.distanceDroit = 0;
	unRobot.distanceGauche = 0;
	unRobot.totalDistanceDroit = 0;
	unRobot.totalDistanceGauche = 0;


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
    	}


    return 0;
}
