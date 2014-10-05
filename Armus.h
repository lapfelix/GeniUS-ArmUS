/*
 * Programme Armus - Équipe P24
 * Création : 01/10/2014
 * Modifié  : 02/10/2014
 */


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
};
void setVitesse(robot&,int&,const short int);
int distance();

//TEST
void setVitesseTEST(robot&,int&,const short int);

void cmToRevolution(int cm,robot &unRobot,int &i,const short int TRANSITIONS);
void parcours(robot &unRobot,int &i,const short int TRANSITIONS);
void setAngle(int angle,robot &unRobot,int &i,const short int TRANSITIONS);
