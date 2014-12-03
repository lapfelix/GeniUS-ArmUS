/*
 * main.cpp
 *
 *  Created on: 2014-11-09
 *      Author: DaeSoluS
 */
#include "Robot.h"
#include "Tests.h"
#include <libarmus.h>
#include "Jeu.h"
using namespace std;

int main()
{
	bool laDerniereCarte = false;
	pthread_t thread_scan;//Thread du scanneur NFC
	Robot unRobot(10);	//10 �tant les transitions (vitesse) du robot

<<<<<<< HEAD

	unRobot.mAJdesLumieres(0,1,1,1);
=======
	LCD_SetMonitorMode(LCD_ONLY);
	LCD_ClearAndPrint("Bonjour, et Bienvenue! Je m'appelle R2D3\n\nVeuillez selectionner un niveau de difficulte:\n");
	LCD_Printf("Facile : Vert\nMoyen : Jaune\nDifficile : Rouge\n");

	//affaires de test
	//test de couleur si bouton du haut
	if(DIGITALIO_Read(14)){
		LCD_Printf("\nTEST COULEURS\n");
			testCouleur();
	}

>>>>>>> origin/CRJ
	int lastNfcScan = 0;
	unRobot.setButtonPress();

	Jeu jeu(unRobot.getCurrentButton());
	LCD_Printf("\n");
	LCD_Printf(jeu.lireQuestion());

	THREAD_Create(&thread_scan,&Robot::scanPointer,&unRobot);

	while(1)
	{
		unRobot.avancer();
		int nfcResult = unRobot.lireScan();
		if(nfcResult != 0 && nfcResult != lastNfcScan)
		{
			jeu.jouer(nfcResult);
			LCD_Printf("\n POINT: %i/8",jeu.lirePointage());
			lastNfcScan = nfcResult;
		}
	}
	return 0;
}



