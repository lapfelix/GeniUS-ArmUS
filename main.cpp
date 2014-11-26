/*
 * main.cpp
 *
 *  Created on: 2014-11-09
 *      Author: DaeSoluS
 */
#include "Robot.h"
#include <libarmus.h>

using namespace std;

int main()
{

	bool laDerniereCarte = false;
	Robot unRobot(10);
	AUDIO_SetVolume(80);
	unsigned int music, state = 0;



	LCD_ClearAndPrint("Bonjour, et Bienvenue! Je m'appelle R2D3\n\nVeuillez selectionner un niveau de difficulte:\n");
	LCD_Printf("Facile : Vert\nMoyen : Jaune\nDifficile : Rouge\n");

	//TODO: Aller au milieu, pivoter pet faire face au publique

	while(1)
	{



	unRobot.setButtonPress();


	if(unRobot.getCurrentButton()!=0)
	{

		switch(unRobot.getCurrentButton()){
			    case 1 :
			    	LCD_ClearAndPrint("Facile!");
			       break;
			    case 2 :
			    	LCD_ClearAndPrint("Moyen!");
			 	       break;
			    case 3 :
			    	LCD_ClearAndPrint("Difficile!");
			 	       break;
			    default :
			           break;
			}



	 unRobot.lireSon("yeah.wav");
	 LCD_ClearAndPrint("\n\nQue le jeux commence!\n\nPret?\nAppuyer sur une touche pour commencer.");

	 //Rappelle la demande d'appuie sur un bouton
	 unRobot.setButtonPress();
	 //TODO:
	}
	}

	return 0;

}
