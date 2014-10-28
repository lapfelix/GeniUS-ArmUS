
#include "CapteurCouleur.h"
#include "CapteurCouleurAnalogue.h"
#include "Colors.h"
#include "colorConvert.h"

#include <cmath>


#define WHITE_COLOR				0
#define BLUE_COLOR				1
#define RED_COLOR				2
#define GREEN_COLOR				3
#define YELLOW_COLOR			4

#define BLUE_HUE				0.365
#define RED_HUE					0.975
#define GREEN_HUE				0.530
#define YELLOW_HUE				0.870

//string colorNames[6] = {"BLANC","BLEU","VERT","ROUGE","JAUNE","WTF"};

bool checkSameHue(float, float);
int currentFloorColor(HsbColor);
int currentFloorColorA(HsbColor);
void testCouleur();
