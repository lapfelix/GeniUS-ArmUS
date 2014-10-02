/*
 * Programme Armus - Équipe P24
 * Création : 01/10/2014
 * Modifié  : 02/10/2014
 */
#include <iostream>
#include <libarmus.h>
#include <cmath>
#include "Armus.h"
int main()
{
	const short int VITESSE_INITIALE = 50;
	const short int TRANSITIONS = 20;
	const short int MODE = 1; // TEST:0 DEV:1

	int i = 1; //nb de cycle**

	robot unRobot;
	unRobot.vitesseDroit = VITESSE_INITIALE;
	unRobot.vitesseGauche = VITESSE_INITIALE+2;
	unRobot.distanceDroit = 0;
	unRobot.distanceGauche = 0;

    LCD_ClearAndPrint("New\n");
    while(true)
    {
    	if(MODE == 0)
    	{
    	    setVitesseTEST(unRobot,i,TRANSITIONS);
    	}
    	else if(MODE == 1)
    	{
    		setVitesse(unRobot,i,TRANSITIONS);
    	}
        i++;
    }
    return 0;
}


