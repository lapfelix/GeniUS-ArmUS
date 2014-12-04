/*
 * Robot.h
 *
 *  Created on: 2014-11-09
 *      Author: DaeSoluS
 */
#include "NFC.h"
#include "Jeu.h" 
#include "CapteurCouleur.h"
#include "Couleur.h"

class Robot
{
private:
	int bouton;
	NFC nfc;
	CapteurCouleur capteurCouleur;
	int lastScan;

	//Capteur unCapteur;
public:
	Robot(int);
	void avancer();
	void tourner(int);
	int PID(int,int,int,int,float);
	void *scan();
	static void *scanPointer(void *context);
	static void *avancerPointer(void *context);
	static void *reculerPointer(void *context);
	static void *couleurPointer(void *context);

	int lireScan();
	void setButtonPress();//Loop qui capte le bouton qui est appuyé
	int getCurrentButton();//Retourne la valeur "bouton" du bouton qui a été appuyé
	void correctionLigne(float&,float&,int&,int&);
	void lireSon(char*);
	void mAJdesLumieres(bool, bool , bool, bool);
	void testCouleur();

	void *scanCouleur(void);
	void *colorLoop(void);

	void tourner180untilLine();

	//Fonction fait bien vite.
	void *avancerAvecLaLigne(void);
	void *reculerAvecLaLigne(void);
	void stopMotors();
	void setVitesse(int,int);
	bool shouldMoveForward;
	bool shouldMoveBackwards;
	int currentColor;
};




