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
	short int MODE=1; //0: TEST   1:	DEV

	//rentre en mode test si le bumper front est enfoncé lorsqu'on pèse sur user
	if(DIGITALIO_Read(BMP_FRONT) == 1)
		MODE=0;

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
