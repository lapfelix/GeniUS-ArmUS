/*
 * Programme Armus - Équipe P24
 * Création : 01/10/2014
 * Modifié  : 02/10/2014
 */
#ifndef COULEUR_H
#define COULEUR_H

#include <math.h>
#include <string>

#include "CapteurCouleur.h"

using namespace std;

/*****************************************************************************
 * ***************************************************************************
 * Couleur.cpp
 * ***************************************************************************
 *****************************************************************************/
#define WHITE_COLOR				0
#define BLUE_COLOR				1
#define RED_COLOR				2
#define GREEN_COLOR				3
#define YELLOW_COLOR			4
#define WTF_COLOR				5
#define BLACK_COLOR				6

#define BLUE_HUE				0.365
#define RED_HUE					0.975
#define GREEN_HUE				0.530
#define YELLOW_HUE				0.870



bool checkSameHue(float, float);
int currentFloorColor(HsbColor, bool);
HsbColor RGBtoHSB(RgbColor );
int readAndGetColor(bool);
#endif
