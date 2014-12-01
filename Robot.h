/*
 * Robot.h
 *
 *  Created on: 2014-11-09
 *      Author: DaeSoluS
 */
#include "NFC.h"
<<<<<<< HEAD
#include "Jeu.h"
=======

>>>>>>> origin/CRJ
class Robot
{
private:
	int transitionsGauche;
	int transitionsDroite;
	int bouton;
	NFC nfc;
<<<<<<< HEAD
	Jeu jeu();
=======

>>>>>>> origin/CRJ

	//Capteur unCapteur;
public:
	Robot(int);
	void avancer(bool);
	void tourner(int);
	int PID(int,int,int,int);
<<<<<<< HEAD
	int lireNfc();
=======
	void lireNfc();

	void setButtonPress();//Loop qui capte le bouton qui est appuyé
	int getCurrentButton();//Retourne la valeur "bouton" du bouton qui a été appuyé

	void lireSon(char*);
>>>>>>> origin/CRJ
};


