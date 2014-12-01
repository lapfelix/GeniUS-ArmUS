#include "Robot.h"
#include <libarmus.h>
#include <math.h>

Robot::Robot(int transitions)
{
	LCD_ClearAndPrint("Debut");
	this->transitionsGauche = transitions;
	this->transitionsDroite = transitions;
	this->bouton = 0;
}

int Robot::lireNfc()
{
	return nfc.scanTag();
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

	//Pour initialiser les compteurs avant le d�but, �vite quelques bogues intermittants.
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





int Robot::getCurrentButton()
{
	return this->bouton;
}



void Robot::setButtonPress()
{
	this->bouton=0;

	while(this->bouton == 0 || this->bouton == 7)
	{
		if(DIGITALIO_Read(21)) //Facile
			bouton = 1;
		else
			if(DIGITALIO_Read(22)) //Moyen
				bouton = 2;
			else
				if(DIGITALIO_Read(23)) //Difficile
					bouton = 3;
				else
					if(DIGITALIO_Read(24)) //Instructions
						bouton = 4;
	}



}







