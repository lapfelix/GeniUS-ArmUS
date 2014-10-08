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
