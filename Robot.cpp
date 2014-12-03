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

//allo pier-luc

int Robot::lireNfc()
{
	return nfc.scanTag();
}


void Robot::avancerAvecLaLigne(bool &derniereCarte)
{
	const int LG=1, LC=2, LD=4, LGC=3, LDC=6, LGD=5; // code binaire pour identifier les capteurs de lignes Gauche / Centre / Droite
		const float correctionRoues = 30; // transitions / TEMPS
int lignePositionActuelle = 0, ligneDernierePosition = 0;
		while(!derniereCarte)
			{
		// Lecture du suiveur de ligne
		lignePositionActuelle = 0;
		if(ANALOG_Read(1)< 750) lignePositionActuelle += LG; // Gauche
		if(ANALOG_Read(2)< 750)lignePositionActuelle += LC; // Centre
		if(ANALOG_Read(3)< 750)lignePositionActuelle += LD; // Droite

		// Analyse de la lecture du suiveur de ligne

		if(lignePositionActuelle==LC)
		{
			if(ligneDernierePosition==LG || ligneDernierePosition ==LGC)
			{//Était trop à droite, correction..
				MOTOR_SetSpeed(7,60);
				MOTOR_SetSpeed(8,40);
			}
			else if(lignePositionActuelle==LD || lignePositionActuelle ==LDC)
			{//Était trop à gauche, correction..
				MOTOR_SetSpeed(7,40);
				MOTOR_SetSpeed(8,60);
			}
			else
			{//Était centre, reste centre
				MOTOR_SetSpeed(7,60);
				MOTOR_SetSpeed(8,60);
			}
		}
		else if(lignePositionActuelle==LG || lignePositionActuelle ==LGC) // si LG c'est que robot tend vers la droite
		{//Est trop à droite
			MOTOR_SetSpeed(7,40);
			MOTOR_SetSpeed(8,60);
		}
		else if (lignePositionActuelle==LD || lignePositionActuelle ==LDC) // si LD c'est que robot tend vers la gauche
		{//Est trop à gauche
			MOTOR_SetSpeed(7,60);
			MOTOR_SetSpeed(8,40);
		}
		else
		{//Si autre chose, juste avancer
			MOTOR_SetSpeed(7,60);
			MOTOR_SetSpeed(8,60);
		}
		ligneDernierePosition = lignePositionActuelle;
	}
}



void Robot::avancer(bool &derniereCarte)
{
	int distanceVoulueGauche = 0;
	int distanceVoulueDroite = 0;
	int distanceMoteurDroit = 0;
	int distanceMoteurGauche= 0;
	float ligneCorrectionDroite =0;
	float ligneCorrectionGauche =0;
	int ligneDernierePosition = 2;//LC
	int lignePositionActuelle =0;
	const int TEMPS = 250;//msecondes
	int vitesseMoteurDroit;
	int vitesseMoteurGauche;
	const int LG=1, LC=2, LD=4, LGC=3, LDC=6, LGD=5; // code binaire pour identifier les capteurs de lignes Gauche / Centre / Droite


	//Condition future: Avancer jusqua la derniere carte ou une autre condition.
	while(!derniereCarte)
	{
		if(ANALOG_Read(1)< 750) lignePositionActuelle += LG; // Gauche
		if(ANALOG_Read(2)< 750)lignePositionActuelle += LC; // Centre
		if(ANALOG_Read(3)< 750)lignePositionActuelle += LD; // Droite
		correctionLigne(ligneCorrectionGauche, ligneCorrectionDroite, ligneDernierePosition, lignePositionActuelle);
		THREAD_MSleep(TEMPS);
		int lectureVitesseDroite = ENCODER_Read(ENCODER_RIGHT);
		int lectureVitesseGauche = ENCODER_Read(ENCODER_LEFT);
		if (lignePositionActuelle == LDC|| lignePositionActuelle == LD){
		distanceVoulueGauche += this->transitionsGauche;
		distanceMoteurGauche += lectureVitesseGauche;}
		else
			vitesseMoteurGauche=0;
		if (lignePositionActuelle == LGC || lignePositionActuelle == LG){
		distanceVoulueDroite += this->transitionsDroite;
		distanceMoteurDroit += lectureVitesseDroite;}
		else
			vitesseMoteurDroit =0;



		if(lignePositionActuelle == LGC || lignePositionActuelle == LG){
		vitesseMoteurDroit = PID(lectureVitesseDroite,distanceMoteurDroit,distanceVoulueDroite,this->transitionsDroite,ligneCorrectionDroite);}
		if(lignePositionActuelle == LDC || lignePositionActuelle == LD){
		vitesseMoteurGauche = PID(lectureVitesseGauche,distanceMoteurGauche,distanceVoulueGauche,this->transitionsGauche,lectureVitesseGauche);}

		MOTOR_SetSpeed(7,vitesseMoteurGauche);
		MOTOR_SetSpeed(8,vitesseMoteurDroit);
	}
	
}
void Robot::correctionLigne(float &ligneCorrectionDroite,float &ligneCorrectionGauche,int &ligneDernierePosition,int &lignePositionActuelle)
{
	const int LG=1, LC=2, LD=4, LGC=3, LDC=6, LGD=5; // code binaire pour identifier les capteurs de lignes Gauche / Centre / Droite
	const float correctionRoues = 30; // transitions / TEMPS

	// Lecture du suiveur de ligne
	lignePositionActuelle = 0;
	if(ANALOG_Read(1)< 750) lignePositionActuelle += LG; // Gauche
	if(ANALOG_Read(2)< 750)lignePositionActuelle += LC; // Centre
	if(ANALOG_Read(3)< 750)lignePositionActuelle += LD; // Droite

	// Analyse de la lecture du suiveur de ligne

	if(lignePositionActuelle==LC)
	{
		ligneCorrectionDroite = 0;
		ligneCorrectionGauche= 0;
	}
	else if((lignePositionActuelle==LG || lignePositionActuelle ==LGC) && ligneDernierePosition == LC) // si LG c'est que robot tend vers la droite
	{
		ligneCorrectionDroite = correctionRoues;
		ligneCorrectionGauche=0;
	}
	else if ((lignePositionActuelle==LD || lignePositionActuelle ==LDC) && ligneDernierePosition == LC) // si LD c'est que robot tend vers la gauche
	{
		ligneCorrectionDroite = 0;
		ligneCorrectionGauche= correctionRoues+2;
	}
	else
	{
		 if (ligneDernierePosition == LG)
		 {
			 ligneCorrectionDroite = correctionRoues;
		     ligneCorrectionGauche = 0;
		     lignePositionActuelle=LG;
		 }
		 else if(ligneDernierePosition == LD)
		 {
			 ligneCorrectionDroite = 0;
			 ligneCorrectionGauche = correctionRoues;
			 lignePositionActuelle=LD;
		 }
		 else
		 {
			 ligneCorrectionDroite=0;
		 }
		 ligneCorrectionGauche=0;
	}
	ligneDernierePosition = lignePositionActuelle;
}

int Robot::PID(int lecture,int distanceReel,int distanceIdeal,int transitions,float facteurCorrection)
{
	const float FC_VITESSE = 1;//facteur de correction de la vitesse
	const float FC_DISTANCE = 0.5;//facteur de correction de la distance

	return (int)(-FC_VITESSE*(float)(lecture-transitions)-(FC_DISTANCE*(float)(distanceReel-distanceIdeal)));
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

int Robot::getCurrentButton()
{
	return this->bouton;
}


//Attend que lutilisateur appuie sur un bouton
void Robot::setButtonPress()
{
	this->bouton=0;
	while(this->bouton == 0 || this->bouton == 7)
	{
		if(DIGITALIO_Read(14)) //Facile
		{
			bouton = 1;
			LCD_Printf("\n Facile");
		}
		else if(DIGITALIO_Read(15)) //Moyen
		{
			bouton = 2;
			LCD_Printf("\n Moyen");
		}
		else if(DIGITALIO_Read(16)) //Difficile
		{
			bouton = 3;
			LCD_Printf("\n Difficile");
		}
		else if(DIGITALIO_Read(13)) //Instructions
			bouton = 4;
	}
}




