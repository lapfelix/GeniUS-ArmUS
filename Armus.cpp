
/*
 * Programme Armus - Equipe P24
 * Creation : 01/10/2014
<<<<<<< HEAD
 * Modifie  : 08/10/2014
=======
 * Modifie  : 04/10/2014
>>>>>>> FETCH_HEAD
 */
#include <iostream>
#include <libarmus.h>
#include <cmath>
#include "Armus.h"
<<<<<<< HEAD

int main()
{
	const short int TRANSITIONS = 10;
	const short int MODE=1; //0: TEST   1:	DEV
	robot unRobot;
	reinitialiser(unRobot);
    LCD_ClearAndPrint("New 1\n");
    switch(MODE)
    {
    	case 0 : parcoursTest(unRobot,TRANSITIONS);break;
    	case 1 : parcours(unRobot,TRANSITIONS);break;
    }
=======


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



>>>>>>> FETCH_HEAD
    return 0;
}
