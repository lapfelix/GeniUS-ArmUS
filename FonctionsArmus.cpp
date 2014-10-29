/*
 *  * Programme Armus - Ã‰quipe P24
 * CrÃ©ation : 01/10/2014
 * ModifiÃ©  : 02/10/2014
 */

#include <iostream>
#include <math.h>
#include <libarmus.h>
#include "Armus.h"


const int TEMPS = 250;//msecondes
const float FC_VITESSE = 1;//facteur de correction de la vitesse
const float FC_DISTANCE = 0.5;//facteur de correction de la distance
bool depart14;
bool depart43;
bool arret = false;
void detectionFrequence();
void avancerDroit();

bool pulse250=true;
int timer3 = 0;


void parcours(robot &unRobot, short int OverrideFrequencyStart)
{
	//Variables
	bool estROBOT43; //ROBOT_43 part en premier!!
	bool premierePasse = true;
	bool premierSonEffectuer = false;
	bool IRgauche=false;
	bool IRdroite=false;
	int couleur=0;
	int sortie=0;

	int timer1=0, //Pour la détection dobjet en avant
		tempsDeTournage; //Pour le temps a tourner
	bool cannette=false;

	//DEPART DES THREADS
	THREAD thread_frequence, thread_couleur;
	thread_frequence = THREAD_CreateSimple(detectionFrequence);
	thread_couleur = THREAD_CreateSimple(getCurrentColor);

if(OverrideFrequencyStart==1)
{
	depart14=true;
	depart43=true;
}
	//PROGRAMME
	//LCD_Printf("start program\n");
	LCD_PrintBmp("genius.bmp");

	while (arret!=true) // Thread detectionFrequence gere l'arret du programme.
	{

		//if (SYSTEM_ReadTimerMSeconds() - timer3>=250)
		//	pulse250=true;


		//METHODE 1 : Les 2 robots utilisent la meme technique sur le parcours
		if (depart14==true || depart43==true)
		{
			if(premierePasse==true)
			{

				//vitesse(unRobot,30,30);

				avancerDroit();

				premierePasse=false;
			}
			//----------------------------------------------
			//-------------Detection Couleur----------------
			//----------------------------------------------
			switch(couleurCourrante())
			{
				case 0:
					//LCD_Printf("BLANC");break;
					break;
				case 1:
					//LCD_Printf("BLEU");break;
					arret=true;
					break;
				case 2:
					//LCD_Printf("ROUGE");break;
					//----------------------------------------------
					//------------Detection conraste----------------
					//----------------------------------------------
					if(getContraste() > 220)
					{
						//Detecte correctement une difference de contraste avec le rouge et le vert seulement!
						//Anyway, on utilise ca juste pour le rouge

						//SI LE CONTRASTE est detecter, le robot se dirige vers le rouge a droite
						//**Le capteur de contraste DOIT etre a droite!

						//Devier vers la gauche
						MOTOR_SetSpeed(7,80);
						MOTOR_SetSpeed(8,100);
						THREAD_MSleep(1000);

						//Redevier
						MOTOR_SetSpeed(7,100);
						MOTOR_SetSpeed(8,80);
						THREAD_MSleep(500);

						avancerDroit();
					}
					else
					{
						//Devier vers la gauche
						MOTOR_SetSpeed(7,100);
						MOTOR_SetSpeed(8,80);
						THREAD_MSleep(1000);

						//Redevier
						MOTOR_SetSpeed(7,80);
						MOTOR_SetSpeed(8,100);
						THREAD_MSleep(500);

						avancerDroit();
					}
					break;
				case 3:
					//LCD_Printf("VERT");break;
					arret=true;
					break;
				case 4:
					//LCD_Printf("JAUNE");break;
					break;
				case 5:
					//LCD_Printf("WTF");break;
					break;
				default:
					//LCD_Printf("default");break;
					break;
			}

			//----------------------------------------------
			//------------Detection Infrarouge--------------
			//----------------------------------------------
			switch(IR_Detect(IR_FRONT))
			{
				case 0: IRgauche=false;IRdroite=false;break;
				case 1: IRdroite=true;IRgauche=false;break;
				case 2: IRdroite=false;IRgauche=true;break;
				case 3: IRdroite=true;IRgauche=true;break;
			}
			//----------------------------------------------
			//tourne a droite si obstacle a gauche
			if(IRgauche==false && IRdroite == false)
			{
					//avance si rien de spécial
					avancerDroit();

			}
			else if(IRgauche==true && IRdroite == false && timer1 != 0)
			{
				//dévie vers la droite si obstacle trouvé
				//***Pas sure que le robot détecte comme faut juste 1 capteur
				MOTOR_SetSpeed(7,100);
				MOTOR_SetSpeed(8,80);
			}
			else if(IRdroite==true && IRdroite == false && timer1 != 0)
			{
				//dévie vers la gauche si obstacle trouvé
				//***Pas sure que le robot détecte comme faut juste 1 capteur
				MOTOR_SetSpeed(7,80);
				MOTOR_SetSpeed(8,100);
			}
			else // 2 détecteurs activés
			{

				//Stop les moteurs
				MOTOR_SetSpeed(7,0);
				MOTOR_SetSpeed(8,0);
				timer1= SYSTEM_ReadTimerMSeconds();

				//Attend 1 secondes
				THREAD_MSleep(1000);

				//Affiche la valeur lu des IR
				//***Si il n'y a plus d'objet devant, il donne 1 au lieu de 3!! On sait pas pourquoi
				LCD_Printf("IR : %d",IR_Detect(IR_FRONT));

				//Les 2 detecteurs sont toujours actifs
				//DONC, ce nest pas un objet mouvant (ce nest pas un robot)
				if(IR_Detect(IR_FRONT) == 1)
				{
					//Tourne a droite sur lui meme tant que le mur est present devant les capteurs
					//pendant 1 secondes! Pas plus compliqué que ca sinon ca chie
					MOTOR_SetSpeed(7,50);
					MOTOR_SetSpeed(8,-50);
					THREAD_MSleep(1000);

					//Avancer pendant 1 seconde
					avancerDroit();
					THREAD_MSleep(1000);

					//Retourner pendant 1 seconde
					MOTOR_SetSpeed(7,-50);
					MOTOR_SetSpeed(8,50);
					THREAD_MSleep(1000);

				}


			}



		}



		/* METHODE 2 : Les 2 robots ont un code different
		if (depart14==true) // Programme du robot 14
			{
			LCD_Printf("depart14\n");
			}

		if (depart43==true) // Programme du robot 43
			LCD_Printf("depart43\n");
		*/
	}

	//Stop les moteurs
	MOTOR_SetSpeed(7,0);
	MOTOR_SetSpeed(8,0);

	LCD_ClearAndPrint("FINI");

}


void avancerDroit()
{
	if(DIGITALIO_Read(9) == 1) //Si bool estRobot43;
	{
		MOTOR_SetSpeed(7,96);
		MOTOR_SetSpeed(8,100);
	}
	else
	{
		MOTOR_SetSpeed(7,100);
		MOTOR_SetSpeed(8,100);
	}
}


//Sert Ã  gerer le depart et l'arret du ou des programmes en fonction de la duree du 5kHz,
//La surveillance du signal se fait en temps reel et sans AUCUN MSLEEP !!!!
void detectionFrequence()
{



	//VÃ©rifie quel est le ROBOT en cours!
	int estROBOT43 = DIGITALIO_Read(9);
	//LCD_Printf("est robot43? %i", estROBOT43);

	bool etatFrequence = false;
	bool initTemps= false;
	bool premierSonEffectuer = false;
	int duree5khz=0;
	int temps = 0;
	//on choisit le bon mode de gestion d'erreur
	ERROR_SetMode(LCD_ONLY);

	while(1)
	{
		bool etatFrequence = DIGITALIO_Read(10);



		//LCD_ClearAndPrint("valeur1=%d/n",duree5khz);
		if(etatFrequence==1 && initTemps == false)
		{
			initTemps = true;
			temps = SYSTEM_ReadTimerMSeconds();
			LCD_Printf("inittemps");
		}

		if (etatFrequence==0 && initTemps == true)
		{
			duree5khz=SYSTEM_ReadTimerMSeconds() - temps;
			initTemps = false;
			LCD_Printf("falldown");

			if (duree5khz < 2100 && duree5khz > 1900)
						{

							//Ecrire la fonction qui fait avancer le robot
							if(premierSonEffectuer == false)
							{
								if(estROBOT43 == false)
								{
									premierSonEffectuer = true;
									//partir le robot 14
									depart14 = true;
								}
								else
									premierSonEffectuer = true;

							}
							else if(premierSonEffectuer == true && estROBOT43 == true)
							{
								//partir le robot 43
								depart43=true;
							}
						}
			//duree5khz < 5500 &&
			else if (duree5khz > 4300 || (SYSTEM_ReadTimerMSeconds() - temps)>4000)
							{
								//Ecrire la fonction qui arrÃªte les robots
								depart14 = false;
								depart43 = false;
								arret = true;
							}




				temps = 0;

			}


		}


	}








