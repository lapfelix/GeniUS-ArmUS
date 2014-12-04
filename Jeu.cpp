#include "Jeu.h"
#include <iostream>
#include <time.h>
#include <libarmus.h>

Jeu::Jeu(int niveau)
{
	this->niveau = niveau;
	this->pointage = 0;
	this->caseRendu = 0;
	initJeu();
}


int* Jeu::niveauFacile()
{
	AUDIO_PlayFile("questionFacile.wav");
	LCD_PrintBmp("questionFacile.bmp");
	int* ordrePlanete = new int[NOMBRECARTES];
	for(int i = 1; i<= NOMBRECARTES;++i)
		ordrePlanete[i-1] = i;

	return ordrePlanete;
}

int* Jeu::niveauMoyen()
{
	AUDIO_PlayFile("questionMoyenne.wav");
	LCD_PrintBmp("questionMoyenne.bmp");
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
	AUDIO_PlayFile("questionDifficile.wav");
	LCD_PrintBmp("questionDifficile.bmp");
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

void Jeu::initJeu()
{
	switch (this->niveau)
	{
		case 1:planete.ordre = niveauFacile();break;
		case 2:planete.ordre = niveauMoyen();break;
		case 3:planete.ordre = niveauDifficile();break;
	}
}

void Jeu::jouer(int carte)
{
	this->pointage += (carte == planete.ordre[caseRendu]) ? 1 : 0;
	this->caseRendu++;
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
void Jeu::lirePointage()
{
	if(pointage!=8)
		AUDIO_PlayFile("R2D2-Scream.wav");
	else
		AUDIO_PlayFile("R2D2-Scream.wav");
	switch(this->pointage)
	{
		case 1:LCD_PrintBmp("1sur8.bmp");break;
		case 2:LCD_PrintBmp("2sur8.bmp");break;
		case 3:LCD_PrintBmp("3sur8.bmp");break;
		case 4:LCD_PrintBmp("4sur8.bmp");break;
		case 5:LCD_PrintBmp("5sur8.bmp");break;
		case 6:LCD_PrintBmp("6sur8.bmp");break;
		case 7:LCD_PrintBmp("7sur8.bmp");break;
		case 8:LCD_PrintBmp("8sur8.bmp");break;
		default:LCD_PrintBmp("0sur8.bmp");break;
	}
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







