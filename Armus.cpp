
/*
 * Programme Armus - Equipe P24
 * Creation : 01/10/2014
 * Modifie  : 08/10/2014
 */
#include <iostream>
#include <libarmus.h>
#include <cmath>
#include "CapteurCouleur.h"
#include "Armus.h"
#include "FonctionInfrarouge.h"
#include "detectionSol.h"
#include "CapteurContraste.h"

int main()
{
	const short int TRANSITIONS = 10;
	short int MODE=3; //0: TEST   1:	DEV

	//rentre en mode test si le bumper front est enfoncé lorsqu'on pèse sur user
	if(DIGITALIO_Read(BMP_FRONT) == 1)
		MODE=0;

	//rentre en mode test couleur si le bumper front est enfoncé lorsqu'on pèse sur user
	if(DIGITALIO_Read(BMP_LEFT) == 1)
			MODE=2;

	if(DIGITALIO_Read(BMP_RIGHT) == 1)
			MODE=3;

	if(DIGITALIO_Read(BMP_REAR) == 1)
			MODE=4;

	robot unRobot;
	reinitialiser(unRobot);
    LCD_ClearAndPrint("New 1\n");
    switch(MODE)
    {
    	case 0 : parcoursTest(unRobot,TRANSITIONS);break;
    	case 1 : parcours(unRobot,TRANSITIONS);break;
    	case 2 : testCouleur();break;
    	case 3 : testInfrarouge();break;
    }

    return 0;
}
