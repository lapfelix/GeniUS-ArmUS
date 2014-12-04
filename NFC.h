/*
 NFC.h
 *
 *  Created on: 2014-11-09
 *      Author: DaeSoluS
 */

#ifndef NFC_H_
#define NFC_H_

#define NFCPIN1  9
#define NFCPIN2	 10
#define NFCPIN3	 11
#define NFCPIN4	 12


class NFC
{
private:
	int arduinoNFCPin1;
	int arduinoNFCPin2;
	int arduinoNFCPin3;
	int arduinoNFCPin4;
	int tag;
	bool scanComplet;//Pour sassurer que le scan nfc est fait avant dobtenir la valeur
public:
	NFC();
	int interpreteDigitalRead();
	bool isNfcReading();
	void scanTag();
	int lireTag();
};

#endif /* NFC_H_ */

