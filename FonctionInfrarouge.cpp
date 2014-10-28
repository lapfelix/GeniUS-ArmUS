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

int LecturePin()
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
}
void testInfrarouge()
{
	int GP2D12 = 0;
	int distanceEstimee = 0;

	LCD_ClearAndPrint("Test Infrarouge\n");
	while(1)
	{
		GP2D12 = LecturePin();
		distanceEstimee = CalculDistance(GP2D12);
		LCD_Printf("%i \n", distanceEstimee);
		if(distanceEstimee > 10 && distanceEstimee <80)
			LCD_Printf("%i cm \n", distanceEstimee);
		else
		{
			LCD_Printf("over \n");
		}
		THREAD_MSleep(100);
	}
}

