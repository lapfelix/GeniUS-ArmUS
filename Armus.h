/*
 * Programme Armus - Équipe P24
 * Création : 01/10/2014
 * Modifié  : 02/10/2014
 */
#ifndef ARMUS_H
#define ARMUS_H

#include <iostream>
#include <libarmus.h>
#include <cmath>
#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include <map>

struct robot
{
    	int vitesseDroit;
		int vitesseGauche;
		short int encodeurDroit;
		short int encodeurGauche;
		int distanceDroit;
		int distanceGauche;
		int totalDistanceDroit;
		int totalDistanceGauche;
		int currentDistanceDroit;
		int currentDistanceGauche;

		int distanceVoulueGauche;
		int distanceVoulueDroite; // distance supposément parcourue par le robot;
		short int lecturevitesseDroite;
		short int lecturevitesseGauche;
		int vitesseMoteurDroit;
		int vitesseMoteurGauche;
		int distanceMoteurDroit;
		int distanceMoteurGauche;
};

struct RgbColor
{
		int r;
		int g;
		int b;
};
struct HsbColor
{
		float hue;
		float saturation;
		float brightness;
};
using namespace std;
/*****************************************************************************
 * ***************************************************************************
 * FonctionsArmus
 * ***************************************************************************
 *****************************************************************************/
int distance();
void vitesse(robot&,short int,short int);
void avancer(int,robot&,short int,short int);
void parcours(robot&,short int);
void reinitialiser(robot&);
void tourner(int, robot&, bool);


/*****************************************************************************
 * ***************************************************************************
 * CapteurContraste
 * ***************************************************************************
 *****************************************************************************/
//
int compareContraste();


/*****************************************************************************
 * ***************************************************************************
 * CapteurCouleur
 * ***************************************************************************
 *****************************************************************************/
#define ADJD_S371_QR999_SADR 	0x74
#define CAP_RED					0x6
#define CAP_GREEN				0x7
#define CAP_BLUE				0x8
#define CAP_CLEAR				0x9
#define INTEGRATION_RED			10
#define INTEGRATION_GREEN		12
#define INTEGRATION_BLUE		14
#define INTEGRATION_CLEAR		16
#define ADJD_REG_CTRL			0
#define ADJD_REG_CONFIG			1
#define DATA_RED_LO				64
#define DATA_GREEN_LO			66
#define DATA_BLUE_LO			68
#define DATA_CLEAR_LO			70

#define CTRL_GSSR				0
#define CTRL_GOFS				1

#define CONFIG_TOFS				0

void initCapteurI2C();
RgbColor getColorI2C();
RgbColor getColorAnalog();


/*****************************************************************************
 * ***************************************************************************
 * DetectionSol
 * ***************************************************************************
 *****************************************************************************/
#define WHITE_COLOR				0
#define BLUE_COLOR				1
#define RED_COLOR				2
#define GREEN_COLOR				3
#define YELLOW_COLOR			4

#define BLUE_HUE				0.365
#define RED_HUE					0.975
#define GREEN_HUE				0.530
#define YELLOW_HUE				0.870

bool checkSameHue(float, float);
int currentFloorColor(HsbColor, bool);
string currentFloorColorAnalog(HsbColor);
HsbColor RGBtoHSB(RgbColor );


/*****************************************************************************
 * ***************************************************************************
 * TEST
 * ***************************************************************************
 *****************************************************************************/
void vitesseTEST(robot&,const short int);
void parcoursTest(robot&, short int);
void encodeurGaucheTest();
void encodeurDroitTest();
void testCouleur();
void testInfrarouge();

#endif
