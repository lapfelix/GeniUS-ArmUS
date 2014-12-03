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
void Test_Des_Entrees_Et_Sorties()
{
    int NFC1=0;
    int NFC2=0;
    int NFC3=0;
    int NFC4=0;
    int PbBleu=0, PbVert=0, PbOrange=0, PbRouge=0;
    int CompteurDeTemps=0;
    int DlGauche, DlCentre, DlDroite;
    unsigned int playback=0;
    bool clignoter=false;
    bool jouermusique=false;
    AUDIO_SetVolume(100);
    while(1)
    {
        if(DIGITALIO_Read(9)) 	NFC1=1;
        else 					NFC1=0;
        if(DIGITALIO_Read(10)) 	NFC2=1;
        else 					NFC2=0;
        if(DIGITALIO_Read(11)) 	NFC3=1;
        else 					NFC3=0;
        if(DIGITALIO_Read(12)) 	NFC4=1;
        else 					NFC4=0;
        if(DIGITALIO_Read(13)) 	PbBleu=1;
        else 					PbBleu=0;
        if(DIGITALIO_Read(14)) 	PbVert=1;
        else 					PbVert=0;
        if(DIGITALIO_Read(15)) 	PbOrange=1;
        else 					PbOrange=0;
        if(DIGITALIO_Read(16)) 	PbRouge=1;
        else 					PbRouge=0;
        // Suiveur de ligne
        if(ANALOG_Read(1)>750) 	DlGauche=1;
        else 					DlGauche=0;
        if(ANALOG_Read(2)>750) 	DlCentre=1;
        else 					DlCentre=0;
        if(ANALOG_Read(3)>750) 	DlDroite=1;
        else 					DlDroite=0;
        
        if (clignoter)	DIGITALIO_WriteByte(2,255);
        else if (clignoter==0) DIGITALIO_WriteByte(2,0);
        if (jouermusique == false)
        {
            playback = AUDIO_PlayFile("R2D2-hey-you.wav");
            jouermusique = true;
        }
        if (AUDIO_IsPlaybackDone(playback))
        {
            jouermusique = false;
        }
        
        
        
        THREAD_MSleep(250);
        CompteurDeTemps++;
        if (CompteurDeTemps>2)
        {
            clignoter = not clignoter;
            CompteurDeTemps=0;
        }
        
        LCD_ClearAndPrint("Valeurs NFC :[ %d], [ %d],[ %d],[ %d]", NFC1,NFC2,NFC3,NFC4);
        LCD_Printf("Etat des 4 boutons :\n");
        LCD_Printf(" bleu = %d - vert =%d - orange =%d - rouge =%d", PbBleu, PbVert, PbOrange, PbRouge);
        LCD_Printf("G [%d]  C [%d]  D [%d]", DlGauche, DlCentre, DlDroite);
    }
}


