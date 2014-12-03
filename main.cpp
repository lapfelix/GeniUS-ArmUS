/*
 * main.cpp
 *
 *  Created on: 2014-11-09
 *      Author: DaeSoluS
 */
#include "Robot.h"
#include <libarmus.h>
#include "Jeu.h"
using namespace std;

int main()
{
	bool laDerniereCarte = false;
	pthread_t thread_scan;//Thread du scanneur NFC
	Robot unRobot(10);	//10 étant les transitions (vitesse) du robot


	unRobot.mAJdesLumieres(0,1,1,1);
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



