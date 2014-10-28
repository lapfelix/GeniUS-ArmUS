/*
 * CapteurContraste.cpp
 *
 *  Created on: 2014-10-26
 *      Author: Éric
 */
/*
 * Programme Armus - Equipe P24
 * Creation : 01/10/2014
 * Modifie  : 08/10/2014
 */
#include <iostream>
#include <libarmus.h>
#include <cmath>



int compareContraste()
{
	LCD_PrintBmp("genius.bmp");
	THREAD_MSleep(1000);
	LCD_ClearAndPrint("Detection du contraste");




 ANALOG_Read(2);
    return 0;
}

void comparerAnalog()
{
	int D1,D2,D3,D4,D5,D6;

	//Les entrées D17 à D5 peuvent être utiliser pour les lecteurs de contraste

	//x = DIGITALIO_Read(y)
	//x = D1 D2 D3 D4 D5 D6 D7 D8
	//y = 1  2  3  4  5  6  7  8

	D1 = ANALOG_Read(1);
	D2 = ANALOG_Read(2);
	//D3 = ANALOG_Read(3);
	//D4 = ANALOG_Read(4);
	D5 = ANALOG_Read(5);
	D6 = ANALOG_Read(6);

	/* D3 et D4 ne seront pas utiliser pour la comparaison de contraste.
	 * On compare la moyenne des 2 extremites.
	 */

	int Dmoy12 = (D1+D2)/2; //L'avant
	int Dmoy56 = (D5+D6)/2; //L'arriere

	if(Dmoy12 == Dmoy56)
	{
		//Si les 2 moyennes sont ENVIRON égal, continuer a avancer SAUF SI est sur ZONE BLEU
	}
	else if(Dmoy12>Dmoy56)
	{
		//Si le contraste avant est plus grand que le contraste arriere,
		//Faire avancer le robot!
	}
	else if(Dmoy12<Dmoy56)
	{
		//Si le contraste avant est plus grand que le contraste arriere,
		//Faire reculer le robot! (il a dépasser les bonnes couleurs)
	}
}

/*int ANALOG _Read(int analog_number)
Retourne la valeur lue sur un port analogique. La valeur retournée
est entre 0 et 1023 et correspond à un signal entre 0 et 5V.
Argument :
 - analog_number: numéro de l'entrée analogique (entre 1 et 8).
Retour :
 - une valeur sur 10 bits (entre 0 et 1023) de la tension de 5V.
 * */


/*
//THREAD!

//thread function prototype
void FonctionThread();
int vfg()
{
//allocate the thread handle
 THREAD thread1;
 //start thread
 thread1 = THREAD_CreateSimple(FonctionThread);
 //THREAD_Destroy(THREAD thread)


 //insert main code here
 //the code will continue executing
 //the code from the funtion FonctionThread will
 // execute at the same time

 //destroy thread (not necessary)
 THREAD_Destroy(&thread1);
 return 0;
}
void FonctionThread()
{
 int temps_de_pause = 1000;
// This part of the code will be executed only one time
LCD_Printf("debut du thread");
while(1)
{
 //this part executes until the thread is destroyed
 THREAD_MSleep(temps_de_pause);
}
}
*/
