/*
 * Jeu.h
 *
 *  Created on: 2014-11-30
 *      Author: DaeSoluS
 */

#ifndef JEU_H_
#define JEU_H_

#include <string.h>
#include <map>
#include <vector>
using namespace std;
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
struct Planete
{
	int* ordre;
	char* question;
};
static const  int NOMBRECARTES = 8;
int niveau;
int caseRendu;
int pointage;
Planete planete;
map<int,char*> questions;
public:
	Jeu(int);
	int* niveauFacile();
	int* niveauMoyen();
	int* niveauDifficile();
	void jouer(int);
	int lirePointage();
	int lireCaseRendu();
	char* lireQuestion();
	int random(int,vector<int> &listeNombre);
	map<int,char*> questionsDifficile();
	void initJeu();
};


#endif /* JEU_H_ */
