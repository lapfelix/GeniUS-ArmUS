/*
 * Robot.h
 *
 *  Created on: 2014-11-09
 *      Author: DaeSoluS
 */
#include "NFC.h"
#include "Jeu.h"
class Robot
{
private:
	int transitionsGauche;
	int transitionsDroite;
	int bouton;
	NFC nfc;

	//Capteur unCapteur;
public:
	Robot(int);
	void avancer(bool&);
	void avancerAvecLaLigne(bool&);
	void tourner(int);
	int PID(int,int,int,int,float);
	int lireNfc();
	void setButtonPress();//Loop qui capte le bouton qui est appuyé
	int getCurrentButton();//Retourne la valeur "bouton" du bouton qui a été appuyé
	void correctionLigne(float&,float&,int&,int&);
	void lireSon(char*);
};


