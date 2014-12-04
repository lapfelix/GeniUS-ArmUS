#include <libarmus.h>
#include <math.h>
#include "NFC.h"


NFC::NFC()
{

	this->arduinoNFCPin1 = 0;
	this->arduinoNFCPin2 = 0;
	this->arduinoNFCPin3 = 0;
	this->arduinoNFCPin4 = 0;
	this->tag = 0;
	this->scanComplet = false;
}

void NFC::scanTag()
{

	while(1)
	{
		THREAD_MSleep(120);
		scanComplet = false;
		arduinoNFCPin1 = DIGITALIO_Read(NFCPIN1); //Pin 7 sur arduino, commence a droite (ex: 0001) 1=> pin7
		arduinoNFCPin2 = DIGITALIO_Read(NFCPIN2); //Pin 6 sur arduino
		arduinoNFCPin3 = DIGITALIO_Read(NFCPIN3); //Pin 5 sur arduino
		arduinoNFCPin4 = DIGITALIO_Read(NFCPIN4); //Pin 4 sur arduino
		scanComplet = true;
	}

}

int NFC::lireTag()
{
	if(isNfcReading())
	{
		return interpreteDigitalRead();
	}
	return 0;
}

bool NFC::isNfcReading()
{
	return (this->arduinoNFCPin1==0 && this->arduinoNFCPin2==0 && this->arduinoNFCPin3==0 && this->arduinoNFCPin4==0) == 0;
}

int NFC::interpreteDigitalRead()
{
	int nombreConverti = 0;
	int base = 1;
	int repetition = 0;
	int nombreBinaire = 0;
	int resultat = 0;
	bool scanPin = false;

	while(!scanPin)
	{
		if(scanComplet)
		{
			nombreBinaire += arduinoNFCPin1 ? 1 : 0;
			nombreBinaire += arduinoNFCPin2 ? 10 : 0;
			nombreBinaire += arduinoNFCPin3 ? 100 : 0;
			nombreBinaire += arduinoNFCPin4 ? 1000 : 0;
			scanPin = true;
		}
	}


	while(nombreBinaire > 0)
	{
		//Conversion du nombre en decimal
		nombreConverti = (nombreBinaire % 10) * base;
		resultat += nombreConverti;
		base *= 2;
		nombreBinaire = nombreBinaire / 10;
	}
	return resultat;
}
