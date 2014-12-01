/*
 * Jeu.h
 *
 *  Created on: 2014-11-30
 *      Author: DaeSoluS
 */

#ifndef JEU_H_
#define JEU_H_
using namespace std;
#include <string>
#include <map>
class Jeu
{
private:
enum planetes
{
	MERCURE =	1,
	VENUS	= 2,
	TERRE	= 3,
	MARS	= 4,
	JUPITER = 5,
	SATURNE =	6,
	URANUS =	7,
	NEPTUNE =	8
};

static const  int NOMBRECARTES = 8;
int niveau;
int caseRendu;
int pointage;
string question;

public:
	Jeu(int);
	int* niveauFacile();
	int* niveauMoyen();
	void niveauDifficile();
	void jouer(int);
	int lirePointage();
	int lireCaseRendu();
	string lireQuestion();
	int random();
};


#endif /* JEU_H_ */
