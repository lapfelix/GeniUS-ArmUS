#include "CapteurCouleurAnalogue.h"

int red = 0;
int green = 0;
int blue = 0;


RgbColor getColorA(){
	RgbColor readColors;

	LCD_ClearAndPrint("Test du HDJD-S822\n");

		while(1)
		{
			DIGITALIO_Write(9, 1);		// met la LED du senseur ON
			THREAD_MSleep (50);
			// lit les 3 canaux de couleurs et compense les différences de sensibilités
			// le rouge etant le canal le plus sensible
			red = ANALOG_Read(1) * 10;
			green = ANALOG_Read(2) * 12;
			blue = ANALOG_Read(3) * 19;
			DIGITALIO_Write(9, 0);		// met la LED du senseur OFF
			LCD_ClearAndPrint("Couleurs:\nRouge: %d\nVert:  %d\nBleu:  %d", red, green, blue);
			THREAD_MSleep (50);
		}
		return readColors;
}


