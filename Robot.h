/*
 * Robot.h
 *
 *  Created on: 2014-11-09
 *      Author: DaeSoluS
 */


#define BOUTON_BLEU			13
#define BOUTON_VERT			14
#define BOUTON_ORANGE		15
#define BOUTON_ROUGE		16

#include "NFC.h"
#include "Jeu.h"
class Robot
{
private:
	int transitionsGauche;
	int transitionsDroite;
	int bouton;
	NFC nfc;
	int lastScan;

	//Capteur unCapteur;
public:
	Robot(int);
	void avancer(bool&);
	void avancerAvecLaLigne(bool&);
	void tourner(int);
	int PID(int,int,int,int,float);
	int lireNfc();
	void *scan();
	static void *scanPointer(void *context);
	int lireScan();
	void setButtonPress();//Loop qui capte le bouton qui est appuyé
	int getCurrentButton();//Retourne la valeur "bouton" du bouton qui a été appuyé
	void correctionLigne(float&,float&,int&,int&);
	void lireSon(char*);
	void mAJdesLumieres(bool, bool , bool, bool);
	void testCouleur();

};


