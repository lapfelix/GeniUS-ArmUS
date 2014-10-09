
/*
 * Programme Armus - Equipe P24
 * Creation : 01/10/2014
 * Modifie  : 08/10/2014
 */
 
#include <iostream>
#include <libarmus.h>
#include <cmath>
#include "Armus.h"

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

    return 0;
}
