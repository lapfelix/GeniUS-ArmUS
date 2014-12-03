#include "Jeu.h"
#include <iostream>
#include <time.h>
#include <libarmus.h>

Jeu::Jeu(int niveau)
{
	this->niveau = niveau;
	this->pointage = 0;
	this->caseRendu = 0;
	this->questions = questionsDifficile();
	initJeu();
}


int* Jeu::niveauFacile()
{
	char question[] = "Placer les planetes allant de la plus proche du soleil a la plus eloignee";
	planete.question = question;
	//Ordre des planètes
	int* ordrePlanete = new int[NOMBRECARTES];
	for(int i = 1; i<= NOMBRECARTES;++i)
		ordrePlanete[i-1] = i;

	return ordrePlanete;
}

int* Jeu::niveauMoyen()
{
	char question[] = "Placer les planètes allant de la plus proche du soleil à la plus éloignée";
	planete.question = question;
	int* ordrePlanete = new int[NOMBRECARTES];
	int i = 0;
	ordrePlanete[i++] = MERCURE;
	ordrePlanete[i++] = MARS;
	ordrePlanete[i++] = VENUS;
	ordrePlanete[i++] = TERRE;
	ordrePlanete[i++] = NEPTUNE;
	ordrePlanete[i++] = URANUS;
	ordrePlanete[i++] = SATURNE;
	ordrePlanete[i++] = JUPITER;
	return ordrePlanete;
}

int* Jeu::niveauDifficile()
{
	int* ordrePlanete = new int[NOMBRECARTES-1];
	int i = 7;
	vector<int> listeNombre;
	for(int j=1;j<=NOMBRECARTES;++j)
	{
		listeNombre.push_back(i);
	}

	ordrePlanete[random(i,listeNombre)] = MERCURE;
	ordrePlanete[random(--i,listeNombre)] = MARS;
	ordrePlanete[random(--i,listeNombre)] = VENUS;
	ordrePlanete[random(--i,listeNombre)] = TERRE;
	ordrePlanete[random(--i,listeNombre)] = NEPTUNE;
	ordrePlanete[random(--i,listeNombre)] = URANUS;
	ordrePlanete[random(--i,listeNombre)] = SATURNE;
	ordrePlanete[random(--i,listeNombre)] = JUPITER;
	return ordrePlanete;
}

map<int,char*> Jeu::questionsDifficile()
{
	map<int,char* > unMap;
	char qMercure[] = "Mon nom est utilisé dans le tableau périodique";
	char qVenus[] = "Je suis la planète la plus brillante vue de la terre";
	char qTerre[] = "Il y a beaucoup de micro-organisme qui m'habite";
	char qMars[] = "On me surnomme la planète rouge, car ma surface contient du fer oxydé";
	char qJupiter[] = "Je suis entouré de 67 satellites, dont Io et Europe";
	char qSaturne[] = "J'ai des anneaux très prononcés";
	char qUranus[] = "Je dois mon nom à la divinité romaine du ciel";
	char qNeptune[]= "Je dois mon nom à la divinité romaine des océans";
	unMap[MERCURE] = qMercure;
	unMap[VENUS] = qVenus;
	unMap[TERRE] = qTerre;
	unMap[MARS] = qMars;
	unMap[JUPITER] = qJupiter;
	unMap[SATURNE] = qSaturne;
	unMap[URANUS] = qUranus;
	unMap[NEPTUNE] = qNeptune;
	return unMap;
}

void Jeu::initJeu()
{
	switch (this->niveau)
	{
		case 1:planete.ordre = niveauFacile();break;
		case 2:planete.ordre = niveauMoyen();break;
		case 3:planete.ordre = niveauDifficile();
			   planete.question = questions[1];
			   LCD_Printf(planete.question);
			   break;
	}
}

void Jeu::jouer(int carte)
{
	this->pointage += (carte == planete.ordre[caseRendu]) ? 1 : 0;
	this->caseRendu++;
	if(this->niveau==3)
		planete.question = questionsDifficile()[planete.ordre[caseRendu]];
}

char* Jeu::lireQuestion()
{
	return planete.question;
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

int Jeu::random(int max,vector<int> &listeNombre)
{
	const int min = 0;
	srand(time(NULL));
	int random = (rand() % (max - min + 1)) + min;
	int result = listeNombre[random];
	listeNombre.erase(listeNombre.begin() + random);
	return result;
}







