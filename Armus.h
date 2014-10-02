/*
 * Programme Armus - Équipe P24
 * Création : 01/10/2014
 * Modifié  : 02/10/2014
 */
struct robot
{
    int vitesseDroit;
		int vitesseGauche;
		unsigned short encodeurDroit;
		unsigned short int encodeurGauche;
		int distanceDroit;
		int distanceGauche;
		int totalDistanceDroit;
		int totalDistanceGauche;
};
void setVitesse(robot&,int&,const short int);
int distance();

//TEST
void setVitesseTEST(robot&,int&,const short int);
