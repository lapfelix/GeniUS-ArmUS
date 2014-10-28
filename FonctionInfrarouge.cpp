/*
 * 	Armus GeniUS
 *
 *  Date 2014-10-26
 *  Auteur : William Grand-Maison
 */

#include <iostream>
#include <math.h>
#include <libarmus.h>
#include "FonctionInfrarouge.h"

// Pour le détecteur de distance qu'on n'utilise plus, il produit trop de bruit dans le circuit de
// fréquence de 5kHz. On utilise maintenant les Diodes Infrarouges en avant à gauche et à droite
// sur chaque robot.

/*int LecturePin()
{
	const int PIN = 6;
	int bit = 0;
	float distance = 0;

	bit = ANALOG_Read(PIN);
	if(bit > 3)
		return -1;
	return (6787.0/(bit- 3.0)) - 4.0;
}

int CalculDistance(int lecture_gp2d12)
	{
	 int val;
	 int a,b;
	 a = lecture_gp2d12 / 10;
	 b = lecture_gp2d12 % 10;
	 val = a * 10 + b;
	 return val;
}*/
void testInfrarouge();
THREAD thread_infrarouge;
void testInfrarouge()
{
	/*int GP2D12 = 0;
	int distanceEstimee = 0;*/

	LCD_ClearAndPrint("Test Infrarouge\n");
		/*GP2D12 = LecturePin();
		distanceEstimee = CalculDistance(GP2D12);
		LCD_Printf("%i \n", distanceEstimee);
		if(distanceEstimee > 10 && distanceEstimee <80)
			LCD_Printf("%i cm \n", distanceEstimee);
		else
		{
			LCD_Printf("over \n");
		}
		THREAD_MSleep(100);*/
		int sortie = 0;
		sortie = IR_Detect(IR_FRONT);
		switch(sortie)
		{
			case 0: LCD_Printf("RIEN\n");break;
			case 1: LCD_Printf("DROITE\n");break;
			case 2: LCD_Printf("GAUCHE\n");break;
			case 3: LCD_Printf("DROITE ET GAUCHE\n");break;
		}
		THREAD_MSleep(100);
}

