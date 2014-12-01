/*
 * main.cpp
 *
 *  Created on: 2014-11-09
 *      Author: DaeSoluS
 */
#include "Robot.h"
int main()
{
	bool laDerniereCarte = false;
	//Robot unRobot(10);
	int niveau = 1;//A changer pour la lecture des boutons

	Jeu jeu(niveau); //A arranger
	while(1)
	{
		int nfc = 1;
		//if(unRobot.lireNfc()!=0)
			//jeu.jouer(unRobot.lireNfc());
		jeu.jouer(nfc);
	}
	return 0;
}



