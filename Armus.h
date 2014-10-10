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

		int distanceVoulueGauche;
		int distanceVoulueDroite; // distance supposément parcourue par le robot;
		short int lecturevitesseDroite;
		short int lecturevitesseGauche;
		int vitesseMoteurDroit;
		int vitesseMoteurGauche;
		int distanceMoteurDroit;
		int distanceMoteurGauche;
};
int distance();
void vitesse(robot&,short int,short int);
void avancer(int,robot&,short int,short int);
void parcours(robot&,short int);
void reinitialiser(robot&);
void tourner(int, robot&, bool);

//TEST
void vitesseTEST(robot&,const short int);
void parcoursTest(robot&, short int);
void encodeurGaucheTest();
void encodeurDroitTest();
