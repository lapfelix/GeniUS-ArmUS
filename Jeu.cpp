#include "Jeu.h"
#include <iostream>
#include <time.h>


Jeu::Jeu(int niveau)
{
	this->niveau = niveau;
	this->pointage = 0;
	this->caseRendu = 0;
}
int* Jeu::niveauFacile()
{

	this->question = "Placer les planètes allant de la plus proche du soleil à la plus éloignée";
	//Ordre des planètes
	int* ordrePlanete = new int[NOMBRECARTES];
	for(int i = 1; i<= NOMBRECARTES;++i)
		ordrePlanete[i-1] = i;

	return ordrePlanete;
}

int* Jeu::niveauMoyen()
{
	this->question = "Placer les planètes de la plus petite à la plus grande";
	//Plus petite a la plus grande
	int* ordrePlanete = new int[NOMBRECARTES];
	int i = 0;
	ordrePlanete[i] = MERCURE;
	ordrePlanete[i++] = MARS;
	ordrePlanete[i++] = VENUS;
	ordrePlanete[i++] = TERRE;
	ordrePlanete[i++] = NEPTUNE;
	ordrePlanete[i++] = URANUS;
	ordrePlanete[i++] = SATURNE;
	ordrePlanete[i++] = JUPITER;
	return ordrePlanete;
}

void Jeu::niveauDifficile()
{
	int* ordrePlanete = new int[NOMBRECARTES];
	int i = 0;
	ordrePlanete[random()] = MERCURE;
	ordrePlanete[random()] = MARS;
	ordrePlanete[random()] = VENUS;
	ordrePlanete[random()] = TERRE;
	ordrePlanete[random()] = NEPTUNE;
	ordrePlanete[random()] = URANUS;
	ordrePlanete[random()] = SATURNE;
	ordrePlanete[random()] = JUPITER;


	map<int,string> unMap;
	unMap[MERCURE] = "Mon nom est utilisé dans le tableau périodique";
	unMap[VENUS] = "Je suis la planète la plus brillante vue de la terre";
	unMap[TERRE] = "Il y a beaucoup de micro-organisme qui m'habite";
	unMap[MARS] = "On me surnomme la planète rouge, car ma surface contient du fer oxydé";
	unMap[JUPITER] = "Je suis entouré de 67 satellites, dont Io et Europe";
	unMap[SATURNE] = "J'ai des anneaux très prononcés";
	unMap[URANUS] = "Je dois mon nom à la divinité romaine du ciel";
	unMap[NEPTUNE] = "Je dois mon nom à la divinité romaine des océans";
}

void Jeu::jouer(int carte)
{
	//Facile
	int* planetes;
	if(this->niveau == 1)
	{
		planetes = niveauFacile();
		this->pointage += (carte == planetes[caseRendu]) ? 1 : 0;
	}
	//Moyen
	else if(this->niveau == 2)
	{
		planetes = niveauMoyen();
		this->pointage += (carte == planetes[caseRendu]) ? 1 : 0;
	}
	else
	{

	}

	this->caseRendu++;
}

string Jeu::lireQuestion()
{
	return this->question;
}

int Jeu::lireCaseRendu()
{
	return this->caseRendu;
}


//A faire plus tard
int Jeu::lirePointage()
{
	return this->pointage;
}

int Jeu::random()
{
	const int min = 1;
	const int max = 8;
	srand(time(NULL));
	return (rand() % (max - min + 1)) + min;
}







