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
	Robot unRobot(10);

	LCD_SetMonitorMode(LCD_ONLY);
	LCD_ClearAndPrint("Bonjour, et Bienvenue! Je m'appelle R2D3\n\nVeuillez selectionner un niveau de difficulte:\n");
	LCD_Printf("Facile : Vert\nMoyen : Jaune\nDifficile : Rouge\n");

	//affaires de test
	//test de couleur si bumper avant
	if(DIGITALIO_Read(BMP_FRONT))
			testCouleur();
	int lastNfcScan = 0;

		unRobot.setButtonPress();

		Jeu jeu(unRobot.getCurrentButton());
		LCD_Printf("\n");
		LCD_Printf(jeu.lireQuestion());
		while(1)
		{
			int nfcResult = unRobot.lireNfc();
			if(nfcResult != 0 && nfcResult != lastNfcScan)
			{
				//unRobot.avancer(unRobot.lireNfc());
				jeu.jouer(nfcResult);
				LCD_Printf("\n POINT: %i/8",jeu.lirePointage());
				lastNfcScan = nfcResult;
			}
		}
	return 0;
}



