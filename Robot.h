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
	NFC nfc;
	Jeu jeu();

	//Capteur unCapteur;
public:
	Robot(int);
	void avancer(bool);
	void tourner(int);
	int PID(int,int,int,int);
	int lireNfc();
};


