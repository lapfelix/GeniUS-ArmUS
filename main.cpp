/*
 * main.cpp
 *
 *  Created on: 2014-11-09
 *      Author: DaeSoluS
 */
#include "Robot.h"
#include "Tests.h"
#include "Couleur.h"
#include <libarmus.h>
#include "Jeu.h"
//#include "LogiqueJeu.h"

using namespace std;

void mainLoop();
void waitingToStartLoop();
void waitUntilColor(int);

Robot unRobot(10);	//10 étant les transitions (vitesse) du robot

int main()
{

	while(true){

	bool laDerniereCarte = false;
	pthread_t thread_scan;//Thread du scanneur NFC
	AUDIO_PlayFile("R2D2-bip-bop.wav");
	unRobot.mAJdesLumieres(0,1,1,1);

	//LCD_SetMonitorMode(MONITOR_OFF);
	//LCD_ClearAndPrint("Bonjour, et Bienvenue! Je m'appelle R2D3\n\nVeuillez selectionner un niveau de difficulte:\n");
	//LCD_Printf("Facile : Vert\nMoyen : Jaune\nDifficile : Rouge\n");

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
	}


	//démarre le thread NFC
	THREAD_Create(&thread_scan,&Robot::scanPointer,&unRobot);

	//initialize i2c color reader
	initCapteurI2C();

	//set le volume du speaker


		//TODO: repenser ça
		mainLoop();
	}

	return 0;
}

void mainLoop(){
	pthread_t thread_avancer, thread_reculer;

	int lastNfcScan = 0;

	unRobot.setButtonPress();
	THREAD_MSleep(1200);
	Jeu jeu(unRobot.getCurrentButton());
	//LCD_Printf("\n");
	waitingToStartLoop();

	THREAD_Create(&thread_avancer,&Robot::avancerPointer,&unRobot);

	while(1)
	{
		int nfcResult = unRobot.lireScan();

		if(nfcResult != 0 && nfcResult != lastNfcScan)
		{
			AUDIO_PlayFile("R2D2-do.wav");
			jeu.jouer(nfcResult);
			//LCD_Printf("\n POINT: %i/8 CARTES: %i RESULT: %i",jeu.lirePointage(),jeu.lireCaseRendu(),nfcResult);
			lastNfcScan = nfcResult;
		}

		if(jeu.lireCaseRendu()==8){
			break;
		}
	}

	//rendu ici on veut du blanc et ensuite du bleu, et on arrête
	//waitUntilColor(WHITE_COLOR);
	//waitUntilColor(BLUE_COLOR);

	unRobot.shouldMoveForward = false;
	if(jeu.lirePointage() != 8)
	{
		AUDIO_PlayFile("R2D2-Scream.wav");
	}
	//LCD_Printf("\nstop. rewind");

	THREAD_MSleep(1000);

	THREAD_Create(&thread_reculer,&Robot::reculerPointer,&unRobot);

	//LCD_Printf("\nJ'ATTEND du blanc 1.");
	waitUntilColor(WHITE_COLOR);
	//LCD_Printf("2.");
	waitUntilColor(WHITE_COLOR);
	//LCD_Printf("3.");
	waitUntilColor(WHITE_COLOR);
	//LCD_Printf("4.");
	waitUntilColor(WHITE_COLOR);
	//LCD_Printf("\nJ'ATTEND du vert");
	waitUntilColor(GREEN_COLOR);

	unRobot.shouldMoveBackwards = false;

	//THREAD_Destroy(&thread_avancer);
}

void waitingToStartLoop(){
	//LCD_Printf("\nJ'ATTEND LE BOUTON BLEU");

	int centreActif = 0; //Seulement le dÈtecteur du centre voit la ligne si centreActif = 1

	bool pretAContinuer = false;

	int i = 0;

	while(pretAContinuer == false)
	{
		i++;


		centreActif = 0; //Seulement le centre voit la ligne si centreActif = 1
			// Lecture du suiveur de ligne
			if(ANALOG_Read(1)<750) centreActif += 2; // Gauche
			if(ANALOG_Read(2)< 750)centreActif += 1; // Centre
			if(ANALOG_Read(3)< 750)centreActif += 2; // Droite


		if(DIGITALIO_Read(13)==0)
		{//Si le bouton n'est pas activé
			if(centreActif==1 && readAndGetColor() == GREEN_COLOR){
				DIGITALIO_Write(15,1);
				//unRobot.mAJdesLumieres(1,0,0,0);

		}else{
				DIGITALIO_Write(15,0);
				//unRobot.mAJdesLumieres(0,0,0,0);

				//flash vite les lumières
				unRobot.mAJdesLumieres(i%2,(i+1)%2,i%2,(i+1)%2);
			}
		}
		else
		{//Si le bouton est activé
			if(centreActif==1 && readAndGetColor() == GREEN_COLOR)//Et si le robot est bien alignee
			{
				DIGITALIO_Write(15,0);
				pretAContinuer=true;
				unRobot.mAJdesLumieres(1,1,1,1);
			}
		}
	}

	THREAD_MSleep(1000);
}

void waitUntilColor(int color){
	while(readAndGetColor()!=color){
		//LCD_Printf("%i",readAndGetColor());

		//THREAD_MSleep(stepTime); //on sleep 50 ms parce qu'on est pas fou malade mental
		//currentTime+=stepTime;
	}
}

