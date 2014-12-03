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
#include "LogiqueJeu.h"

using namespace std;

int main()
{
	bool laDerniereCarte = false;
	pthread_t thread_scan;//Thread du scanneur NFC
	Robot unRobot(10);	//10 étant les transitions (vitesse) du robot

	unRobot.mAJdesLumieres(0,1,1,1);

	LCD_SetMonitorMode(LCD_ONLY);
	LCD_ClearAndPrint("Bonjour, et Bienvenue! Je m'appelle R2D3\n\nVeuillez selectionner un niveau de difficulte:\n");
	LCD_Printf("Facile : Vert\nMoyen : Jaune\nDifficile : Rouge\n");

	//affaires de test
	//test de couleur si bouton vert
	if(DIGITALIO_Read(14)){
		LCD_Printf("\nTEST COULEURS\n");
			testCouleur();
	}

	//test de entrees sorties si bouton orange
		if(DIGITALIO_Read(15)){
			LCD_Printf("\nTEST COULEURS\n");
				Test_Des_Entrees_Et_Sorties();
///////////////////////////////////////////////////////////////////////////////
	//Comment lire un fichier ben relaxe
LCD_ClearAndPrint("Lecture audio");
	AUDIO_SetVolume(100);
	int musique = AUDIO_PlayFile("R2D2-Scream.wav");
	/////////////////////////////////////////////////


	int centreActif = 0; //Seulement le détecteur du centre voit la ligne si centreActif = 1
	bool pretAContinuer = false;

	while(pretAContinuer == false)
	{
		centreActif = 0; //Seulement le centre voit la ligne si centreActif = 1
			// Lecture du suiveur de ligne
			if(ANALOG_Read(1)<750) centreActif += 2; // Gauche
			if(ANALOG_Read(2)< 750)centreActif += 1; // Centre
			if(ANALOG_Read(3)< 750)centreActif += 2; // Droite


		if(DIGITALIO_Read(13)==0)
		{//Si le bouton n'est pas activer
			if(centreActif==1) //TODO: Félix ajoute la détection du vert ici
				DIGITALIO_Write(15,1);
			else
				DIGITALIO_Write(15,0);
		}
		else
		{//Si le bouton est activer
			if(centreActif==1)//TODO: Félix ajoute la détection du vert ici //Et si le robot est bien alignee
			{
				DIGITALIO_Write(15,0);
				pretAContinuer=true;
			}
		}
	}

	//TODO: Entrer ici le code du commencement de l'analyse de la planche de jeu!
    bool DerniereCarte = false; //Mettre cette variable globale dans le Robot.cpp,
    							//pour que le code sache ou yer rendu
	unRobot.avancerAvecLaLigne(DerniereCarte);


///////////////////////////////////////////////////////////////////////////////////////////
	//LCD_ClearAndPrint("Fin");
	return 0;


	int lastNfcScan = 0;

	int lastPlanet = 0;
	unRobot.setButtonPress();

	Jeu jeu(unRobot.getCurrentButton());
	LCD_Printf("\n");
	LCD_Printf(jeu.lireQuestion());

	THREAD_Create(&thread_scan,&Robot::scanPointer,&unRobot);

	startGame();

	//main game loop
	while(1)
	{
		//vérifie si le robot est sur du vert
		if(readAndGetColor() && unRobot.getCurrentButton() == BOUTON_BLEU){{
			unRobot.avancer();
		}
		int currentPlanet = unRobot.lireScan();
		if(currentPlanet != 0 && currentPlanet != lastPlanet)
		{
			jeu.jouer(currentPlanet);
			LCD_Printf("\n POINT: %i/8",jeu.lirePointage());
			lastPlanet = currentPlanet;
		}
	return 0;
}



