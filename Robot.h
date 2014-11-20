/*
 * Robot.h
 *
 *  Created on: 2014-11-09
 *      Author: DaeSoluS
 */
#include "NFC.h"
class Robot
{
private:
	int transitionsGauche;
	int transitionsDroite;
	NFC nfc;
	void lireSon(char*);
	//Capteur unCapteur;
public:
	Robot(int);
	void avancer(bool);
	void tourner(int);
	int PID(int,int,int,int);
	void lireNfc();
};


