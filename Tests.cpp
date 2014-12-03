#include "Tests.h"

void testCouleur()
{
	//TODO: un 'if' qui prend la couleur avec le i2c ou analogue dependant du robot

	//le robot 43 a une pin entre le digital 9 et le Vcc
	bool estRobot43 = true;

	//initialiser le capteur cest important quand on s'appelle robot 43
	if(estRobot43)
		initCapteurI2C();

	//ofstream fichier;
	//fichier.open("couleur.txt");
	while(1)
	{
		RgbColor readColor;
		//step 1
		if(estRobot43)
			readColor = getColorI2C();
		else
			readColor = getColorAnalog();
		LCD_ClearAndPrint("\nR=%i, G=%i, B=%i", readColor.r, readColor.g, readColor.b);

		//fichier << "background-color: rgb(" <<readColor.r<<","<<readColor.g<<","<<readColor.b<<")"<< endl;
		//step 2
        HsbColor colorsHSB = RGBtoHSB(readColor);
		LCD_Printf("\nH=%.4f, S=%.4f, B=%.4f ", colorsHSB.hue, colorsHSB.saturation, colorsHSB.brightness);

		int laCouleur = currentFloorColor(colorsHSB,estRobot43);
		LCD_Printf("\n");
		switch(laCouleur){
					case 0:
						LCD_Printf("BLANC");break;
					case 1:
						LCD_Printf("BLEU");break;
					case 2:
						LCD_Printf("ROSE");break;
					case 3:
						LCD_Printf("VERT");break;
					case 4:
						LCD_Printf("JAUNE");break;
					case 5:
						LCD_Printf("WTF");break;
					case 6:
						LCD_Printf("Noir");break;
					default:
						LCD_Printf("default");break;
				}
	}
}
