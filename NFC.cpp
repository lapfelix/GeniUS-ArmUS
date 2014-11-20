#include <libarmus.h>
#include <math.h>
#include "NFC.h"


NFC::NFC()
{
	this->arduinoNFCPin1 = 0;
	this->arduinoNFCPin2 = 0;
	this->arduinoNFCPin3 = 0;
	this->arduinoNFCPin4 = 0;
}

void NFC::scanTag()
{
	arduinoNFCPin1 = DIGITALIO_Read(NFCPIN1); //Pin 7 sur arduino, commence a droite (ex: 0001) 1=> pin7
	arduinoNFCPin2 = DIGITALIO_Read(NFCPIN2); //Pin 6 sur arduino
	arduinoNFCPin3 = DIGITALIO_Read(NFCPIN3); //Pin 5 sur arduino
	arduinoNFCPin4 = DIGITALIO_Read(NFCPIN4); //Pin 4 sur arduino

	if(isNfcReading())
	{
		int tag = interpreteDigitalRead();
		LCD_Printf("\n %i ",tag);
	}
}

bool NFC::isNfcReading()
{
	return (this->arduinoNFCPin1==0 && this->arduinoNFCPin2==0 && this->arduinoNFCPin3==0 && this->arduinoNFCPin4==0) == 0;
}



int NFC::interpreteDigitalRead()
{
	int nombreConverti = 0;
	int exposant = 0;
	int repetition = 0;
	int nombreBinaire = 0;
	int resultat = 0;

	nombreBinaire += arduinoNFCPin1 ? 1 : 0;
	nombreBinaire += arduinoNFCPin2 ? 10 : 0;
	nombreBinaire += arduinoNFCPin3 ? 100 : 0;
	nombreBinaire += arduinoNFCPin4 ? 1000 : 0;

	do
	{
		//Conversion du nombre en decimal
		nombreConverti = nombreBinaire % 10;
		resultat += nombreConverti * (int)(pow((double) 2, exposant));
		nombreBinaire = nombreBinaire / 10;
		exposant++;

	}	while(nombreBinaire != 0);
	return resultat;
}
