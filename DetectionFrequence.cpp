/*
============================================================================
 Name : Frequence.cpp
 Author : Pier-Luc LeDominateur Côté, Ian LapinFidel Lachance  & Eric BlackMelon Matte
 Version : 1.1
 Description : Detection de frequence 5kHz
============================================================================
*/

// Include Files
#include <libarmus.h>

//Variables
bool estROBOT43; //ROBOT_43 part en premier!!
bool premierSonEffectuer = false;

//Fonctions
bool freq_watch();
int etat_robot(float temps);


int main4()
{
	SYSTEM_ResetTimer();

	//Vérifie quel est le ROBOT en cours!
	estROBOT43 = DIGITALIO_Read(9);
	LCD_Printf("est robot43? %i", estROBOT43);

	return 0;

	bool etatFrequence = false;
	bool initTemps= false;
	int duree5khz=0;
	//on choisit le bon mode de gestion d'erreur
	ERROR_SetMode(LCD_ONLY);

	while(1)
	{
		LCD_Printf("etatFrequence");
		bool etatFrequence = freq_watch();

		int temps = 0;

		LCD_ClearAndPrint("valeur1=%d/n",duree5khz);
		if(etatFrequence==1 && initTemps == false)
		{
			initTemps = true;
			temps = SYSTEM_ReadTimerMSeconds();
		}

		if (etatFrequence==0 && initTemps == true)
		{
			duree5khz=SYSTEM_ReadTimerMSeconds() - temps;
			initTemps = false;


		etat_robot(duree5khz);
		}
		LCD_Printf("fin");

	}


	// On arrete tout sur la carte d'entrees/sorties
		FPGA_StopAll();
		return 0;
}


int etat_robot(float temps) //Verifier la reinisialisation du pointeur
{
if (temps < 2100 && temps > 1900)
	{

	//Ecrire la fonction qui fait avancer le robot
	if(estROBOT43 == false && premierSonEffectuer == false)
	{
			premierSonEffectuer = true;
			//Wait
			return 0;
	}


	// -> START

	}
else if (temps < 5200 && temps > 4800)
	{
		//Ecrire la fonction qui arrête le robot
	}

	temps = 0;
	return 0;
}


bool freq_watch()
{
	return DIGITALIO_Read(10);
}

