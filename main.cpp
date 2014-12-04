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
#include "Tests.h"
//#include "LogiqueJeu.h"

using namespace std;

void mainLoop();
void waitingToStartLoop();
void waitUntilColor(int);

Robot unRobot(10);	//10 étant les transitions (vitesse) du robot

int main()
{
	bool laDerniereCarte = false;
	pthread_t thread_scan;//Thread du scanneur NFC
	AUDIO_PlayFile("R2D2-bip-bop.wav");
	unRobot.mAJdesLumieres(0,1,1,1);
	test();


	//démarre le thread NFC
	THREAD_Create(&thread_scan,&Robot::scanPointer,&unRobot);


	while(true){
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
	waitingToStartLoop();

	THREAD_Create(&thread_avancer,&Robot::avancerPointer,&unRobot);

	while(1)
	{
		int nfcResult = unRobot.lireScan();

		if(nfcResult != 0 && nfcResult != lastNfcScan)
		{
			AUDIO_PlayFile("R2D2-do.wav");
			jeu.jouer(nfcResult);
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

	//THREAD_MSleep(1000);
	//THREAD_Create(&thread_reculer,&Robot::reculerPointer,&unRobot);

	jeu.lirePointage();
	unRobot.shouldMoveBackwards = false;
}

void waitingToStartLoop(){

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


		if(DIGITALIO_Read(13)==0 && centreActif==1)
		{
			//Si le bouton n'est pas activé
			DIGITALIO_Write(15,1);
			unRobot.mAJdesLumieres(1,0,0,0);
		}
		else if(DIGITALIO_Read(13)==1 && centreActif==1)
		{
			DIGITALIO_Write(15,0);
			pretAContinuer=true;
			unRobot.mAJdesLumieres(0,1,1,1);
		}
		else
		{
			DIGITALIO_Write(15,0);
			unRobot.mAJdesLumieres(i%2,(i+1)%2,i%2,(i+1)%2);
		}
	}

	THREAD_MSleep(1000);
}

void waitUntilColor(int couleur){
	while(unRobot.)
}
