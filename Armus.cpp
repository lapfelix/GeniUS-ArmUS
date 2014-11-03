
/*
 * Programme Armus - Equipe P24
 * Creation : 01/10/2014
 * Modifie  : 08/10/2014
 */
#include "Armus.h"

int main()
{
	const short int TRANSITIONS = 10;
	short int MODE=1; //0: TEST   1:	DEV

	//rentre en mode test si le bumper front est enfoncé lorsqu'on pèse sur user
	if(DIGITALIO_Read(BMP_FRONT) == 1)
		MODE=0;

	//rentre en mode test couleur si le bumper front est enfoncé lorsqu'on pèse sur user
	if(DIGITALIO_Read(BMP_LEFT) == 1)
			MODE=2;

	if(DIGITALIO_Read(BMP_RIGHT) == 1)
			MODE=3;

	if(DIGITALIO_Read(BMP_REAR) == 1)
			MODE=5;

	if(DIGITALIO_Read(BMP_FRONT) == 1 && DIGITALIO_Read(BMP_REAR) == 1)
			MODE=4;

	robot unRobot;
	//reinitialiser(unRobot);
    LCD_ClearAndPrint("v 2\n");
    switch(MODE)
    {
    	case 0 : parcoursTest(unRobot,TRANSITIONS);break;
    	case 1 : parcours2(unRobot, false);break;
    	case 2 : testCouleur();break;
    	case 3 : testInfrarouge();break;
    	case 4 : testDistance();break;
    	case 5 : parcours2(unRobot, true);break;
    }

    return 0;
}
