#include "Robot.h"
#include <libarmus.h>
#include <math.h>

Robot::Robot(int transitions)
{
	LCD_ClearAndPrint("Debut");
	this->transitionsGauche = transitions;
	this->transitionsDroite = transitions;
}

void Robot::lireNfc()
{
	int tagNumber, lastTag = -1;
	while(true)
	{
		tagNumber = nfc.scanTag();

		if (tagNumber!=0 && tagNumber != lastTag){
			lastTag = tagNumber;
			//string fileName = "son%i.wav",tagNumber; "son%i.wav",tagNumber
			char fileName[50];
			sprintf(fileName, "son%i.wav", tagNumber);
			lireSon(fileName);
		}
	}
}

void Robot::avancer(bool derniereCarte)
{
	int distanceVoulueGauche = 0;
	int distanceVoulueDroite = 0;
	int distanceMoteurDroit = 0;
	int distanceMoteurGauche= 0;
	const int TEMPS = 250;//msecondes

	//Condition future: Avancer jusqua la derniere carte ou une autre condition.
	while(!derniereCarte)
	{
		THREAD_MSleep(TEMPS);
		int lectureVitesseDroite = ENCODER_Read(ENCODER_RIGHT);
		int lectureVitesseGauche = ENCODER_Read(ENCODER_LEFT);
		distanceVoulueGauche += this->transitionsGauche;
		distanceVoulueDroite += this->transitionsDroite;
		distanceMoteurDroit += lectureVitesseDroite;
		distanceMoteurGauche += lectureVitesseGauche;

		int vitesseMoteurDroit = PID(lectureVitesseDroite,distanceMoteurDroit,distanceVoulueDroite,this->transitionsDroite);
		int vitesseMoteurGauche = PID(lectureVitesseDroite,distanceMoteurGauche,distanceVoulueGauche,this->transitionsGauche);

		MOTOR_SetSpeed(7,vitesseMoteurGauche);
		MOTOR_SetSpeed(8,vitesseMoteurDroit);
	}
}
int Robot::PID(int lecture,int distanceReel,int distanceIdeal,int transitions)
{
	const float FC_VITESSE = 1;//facteur de correction de la vitesse
	const float FC_DISTANCE = 0.5;//facteur de correction de la distance

	return (int)(-FC_VITESSE*(float)(lecture-transitions)-FC_DISTANCE*(float)(distanceReel-distanceIdeal));
}



//angle 90 degrees
void Robot::tourner(int angle)
{
	float tourCompletCm = 1.604;

	//Pour initialiser les compteurs avant le début, évite quelques bogues intermittants.
	int init;
	init=ENCODER_Read(ENCODER_LEFT);

	int distance = 0;
	while(distance <= (int)((angle - 15)/tourCompletCm))
	{
		distance += ENCODER_Read(ENCODER_LEFT);
		MOTOR_SetSpeed(MOTOR_LEFT,35);
		LCD_Printf("%i\n",distance);
	}
}

void Robot::lireSon(char fileName[50]){
	int stream = AUDIO_PlayFile(fileName);
	while(!AUDIO_IsPlaybackDone(stream))
		THREAD_MSleep(100);
}









