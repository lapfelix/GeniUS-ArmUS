//parce que jsuis bs
#define ln     LCD_Printf("\n")

#include "detectionSol.h"

float hues[4] = {BLUE_HUE,RED_HUE,GREEN_HUE,YELLOW_HUE};

void testCouleur()
{
	//TODO: un 'if' qui prend la couleur avec le i2c ou analogue dependant du robot

	//le robot 43 a une pin entre le digital 9 et le Vcc
	bool estRobot43 = (DIGITALIO_Read(9) == 1);

	//initialiser le capteur cest important quand on s'appelle robot 43
	if(estRobot43)
		initCapteur();

	while(1)
	{
		RgbColor readColor;
		//step 1
		if(estRobot43)
			readColor = getColor();
		else
			readColor = getColorA();

		LCD_ClearAndPrint("R=%d, G=%d, B=%d", readColor.r, readColor.g, readColor.b);

		//step 2
        HsbColor colorsHSB = RGBtoHSB(readColor);
        ln;
		LCD_Printf("H=%.4f, S=%.4f, B=%.4f", colorsHSB.hue, colorsHSB.saturation, colorsHSB.brightness);
		ln;ln;

		int laCouleur;

		if(estRobot43)
			laCouleur = currentFloorColor(colorsHSB);
		else
			laCouleur = currentFloorColorA(colorsHSB);

		//step 3
		switch(laCouleur){
			case 0:
				LCD_Printf("BLANC");break;
			case 1:
				LCD_Printf("BLEU");break;
			case 2:
				LCD_Printf("ROUGE");break;
			case 3:
				LCD_Printf("VERT");break;
			case 4:
				LCD_Printf("JAUNE");break;
			case 5:
				LCD_Printf("WTF");break;
			default:
				LCD_Printf("default");break;
		}

		THREAD_MSleep(10);
	}

}

int currentFloorColor(HsbColor readColor)
{

	//algorithme pour detecter le blanc (ça inclut le gris foncé et mm le noir, pour être encore plus fiable)
	if((readColor.saturation < 0.3 && readColor.brightness > 0.38) || readColor.saturation < 0.2)
		return WHITE_COLOR;

	for(int i = 0; i<4; i++)
	{
		if(checkSameHue(readColor.hue,hues[i]))
		{
			return i+1;
		}
	}

	// 5 etant la valeur 'WTF'
	return 5;

}
int currentFloorColorA(HsbColor readColor)
{
	//TODO: Calibrer ça pour le lecteur analogue. Là yé pas calibré pantoute.

	//algorithme pour detecter le blanc (ça inclut le gris foncé et mm le noir, pour être encore plus fiable)
	if((readColor.saturation < 0.3 && readColor.brightness > 0.38) || readColor.saturation < 0.2)
		return WHITE_COLOR;

	for(int i = 0; i<4; i++)
	{
		if(checkSameHue(readColor.hue,hues[i]))
		{
			return i+1;
		}
	}

	// 5 etant la valeur 'WTF'
	return 5;

}

bool checkSameHue(float hue1, float hue2)
{
	float difference = abs(hue1-hue2);
	if(difference > 0.5)
		difference = 1-difference;

	if(difference < 0.07f)
		return true;
	else
		return false;

}
