/*
 *  * Programme Armus - √âquipe P24
 * Cr√©ation : 01/10/2014
 * Modifi√©  : 02/10/2014
 */

#include <iostream>
#include <math.h>
#include <libarmus.h>
#include "Armus.h"

#define LCD_Printf			LCD_Printf("\n"); LCD_Printf

const int TEMPS = 250;//msecondes
const float FC_VITESSE = 1;//facteur de correction de la vitesse
const float FC_DISTANCE = 0.5;//facteur de correction de la distance
bool depart14 = false;
bool depart43 = false;
bool arret = false;
void detectionFrequence();
void detectionStartFrequence();
void avancerDroit();
void getColorThread();
void deviation(int deviationDroite);
void reverseDeviation(int deviationDroite);
void gameOver();
void reculerDroit();
void surLeVert();
void atteintLeBleu();

robot unRobot;

bool pulse250=true;
int timer3 = 0;
int currentColor = -1;
int level = 0;

int left43 = 92;
int right43 = 100;
int left14 = 99 ;
int right14 = 100;

void parcours2(robot &leRobot, bool bypassFrequency)
{
	unRobot = leRobot;
  //variables a Pier-Luc bam d'un coup
  unRobot.distanceVoulueGauche = 0;
  unRobot.distanceVoulueDroite = 0; // distance supposÈment parcourue par le robot;
  unRobot.lecturevitesseDroite = 0;
  unRobot.lecturevitesseGauche = 0;
  unRobot.vitesseMoteurDroit = 0;
  unRobot.vitesseMoteurGauche = 0;
  unRobot.distanceMoteurDroit=0;
  unRobot.distanceMoteurGauche=0;
  unRobot.estRobot43 = DIGITALIO_Read(9);

  if(unRobot.estRobot43)
  {
	  initCapteurI2C();
  }
  LCD_Printf("\nDÈbut detection frequence depart");
  //run cte fonction l‡ jusqu'‡ ce que le robot doive partir
  //TODO:FUCK IT J'OVERRIDE POUR QUE CA PARTE RIGHT AWAY
  if(bypassFrequency == false)//(DIGITALIO_Read(BMP_RIGHT))
  {
	  detectionStartFrequence();
	  if(unRobot.estRobot43)
	  {
		  LCD_Printf("zzzzz");
		  THREAD_MSleep(45000);
		  LCD_Printf("J'ATTEND LE 2e woohoo");
		  detectionStartFrequence();
	  }
  }

  avancerDroit();
  THREAD_MSleep(1500);

  LCD_Printf("\nCrÈation du thread de frÈquence de fin...");
  //part le thread pour la detection de son de fin
  THREAD thread_frequence = THREAD_CreateSimple(detectionFrequence);
  THREAD color_thread = THREAD_CreateSimple(getColorThread);

  LCD_Printf("\nLet's go!");
  //main loop de parcours

  int totalVirageDroite = 0, lastTotalVirageDroite = -1;

	bool surRouge = false;

	int tempsSurRouge = 0;
	int rougeDroit = -1;
	int counter = 0;
	//long float timeSinceRed = 0;


	float startTimer = SYSTEM_ReadTimerMSeconds();

  while(true)
  {
		if(DIGITALIO_Read(BMP_FRONT) == 1){
			//si collision avant
			reculerDroit();
			THREAD_MSleep(750);
		}else if( DIGITALIO_Read(BMP_LEFT) == 1){
			reverseDeviation(-80);
			totalVirageDroite--;
			THREAD_MSleep(330);
		}else if( DIGITALIO_Read(BMP_RIGHT) == 1){
			reverseDeviation(80);
			totalVirageDroite++;
			THREAD_MSleep(330);
		}


	  counter++;
	  bool IRgauche, IRdroite, rectification = false;

	LCD_ClearAndPrint("totalVirageDroite: %i\nLevel: %i\nTempsSurRouge: %i",totalVirageDroite,level,tempsSurRouge);

	switch(currentColor){
						case WHITE_COLOR:
							//blanc
							rougeDroit = -1;
							if(level>=1){
								//fuck ! On est sorti du cercle jaune!
								int nbEssais = 0;
								while(currentColor != 4){
									nbEssais++;
									reculerDroit();
									THREAD_MSleep(100);
									if(nbEssais > 9){
										break;
									}
								}



								nbEssais++;
								reverseDeviation(100);
								totalVirageDroite++;
								totalVirageDroite++;
								totalVirageDroite++;
								totalVirageDroite++;
								totalVirageDroite++;
								totalVirageDroite++;
								totalVirageDroite++;
								THREAD_MSleep(1550);

								if(nbEssais > 10){
									//shit.
									level = 0;
								}

							}/*else{
								if(totalVirageDroite > 3){

									deviation(-100);
									totalVirageDroite--;
									totalVirageDroite--;
									THREAD_MSleep(550);
								}else if(totalVirageDroite < -3){

									deviation(100);
									totalVirageDroite++;
									totalVirageDroite++;
									THREAD_MSleep(550);
								}
							}*/
							LCD_Printf("BLANC"); surRouge = false; break;
						case BLUE_COLOR:
							LCD_Printf("BLEU"); atteintLeBleu(); surRouge = false; break;
						case RED_COLOR:
							reculerDroit();
							THREAD_MSleep(800);
							//si on est sur le rouge et que totalVirageDroite = 0. Ça veut dire que ca a dévié d'un bord
							//on doit donc assumer que totalVirageDroite = 1 ou -1
							if(totalVirageDroite == 0)
								totalVirageDroite = -1;

							LCD_Printf("ROUGE. MAYDAY. MAYDAY");

														//if(!surRouge){
														 surRouge = true;

														 lastTotalVirageDroite = totalVirageDroite;

														if(totalVirageDroite>0){
													    	  deviation(-100);
													    	  totalVirageDroite--;
														      THREAD_MSleep(700);
															  avancerDroit();
															  THREAD_MSleep(75);
															while(currentColor == RED_COLOR){
																/*if(totalVirageDroite > 1){
														    	  deviation(-80);
														    	  totalVirageDroite--;
															      THREAD_MSleep(250);
																}*/
															//on est probablement √† droite.
													    	  deviation(-100);
													    	  totalVirageDroite--;
														      THREAD_MSleep(250);
															  avancerDroit();
															  THREAD_MSleep(75);
															}
														}else{
															  deviation(100);
															  totalVirageDroite++;
															  THREAD_MSleep(700);
															  avancerDroit();
															  THREAD_MSleep(75);
															//on est probablement √† gauche
															while(currentColor == RED_COLOR){
																/*if(totalVirageDroite > 1){
																	  deviation(80);
																	  totalVirageDroite++;
																	  THREAD_MSleep(250);
																}*/
															  deviation(100);
															  totalVirageDroite++;
															  THREAD_MSleep(250);
															  avancerDroit();
															  THREAD_MSleep(75);
															}
														}
														//}
														break;

						case GREEN_COLOR:
							LCD_Printf("VERT");surLeVert(); surRouge = false; break;
						case YELLOW_COLOR:
							LCD_Printf("JAUNE");
							if(level>=2){
								//fuck ! On est sorti du cercle vert!
								int nbEssais = 0;
								while(currentColor != GREEN_COLOR){
									nbEssais++;
									reculerDroit();
									THREAD_MSleep(100);
									if(nbEssais > 9){
										break;
									}
								}



								nbEssais++;
								reverseDeviation(100);
								totalVirageDroite++;
								totalVirageDroite++;
								totalVirageDroite++;
								totalVirageDroite++;
								totalVirageDroite++;
								THREAD_MSleep(1250);

								if(nbEssais > 10){
									//shit.
									level = 1;
								}

							}
							//level 1 !
							//set le level. on peut pas baisser de level. on fait juste chercher le prochain level
							THREAD_MSleep(200);
							if(currentColor == 4){
								THREAD_MSleep(200);
								if(currentColor == 4){
									if(level < 1)
										level = 1;
								//à partir d'ici ya pu jamais de noir. le noir cest le vert
								}
							}
							surRouge = false; break;
						case WTF_COLOR:
							LCD_Printf("WTF"); surRouge = false; break;
						case BLACK_COLOR:
							LCD_Printf("NOIR");
							if(level > 0)
							{
								surLeVert();
							}
							surRouge = false;
							break;
						default:
							LCD_Printf("default"); surRouge = false; break;
					}

	switch(IR_Detect(IR_FRONT))
		      {
		          case 0: IRgauche=false;IRdroite=false;break;
		          case 1: IRdroite=true;IRgauche=false;break;
		          case 2: IRdroite=false;IRgauche=true;break;
		          case 3: IRdroite=true;IRgauche=true;break;
		      }
		      //----------------------------------------------

			//si on est sur le rouge, on se fout des IR sensors
			if(currentColor != 2){
		      if(!IRgauche && !IRdroite)
		      {
		    	  //if((totalVirageDroite < 2 || totalVirageDroite > -2) && !rectification){
		    	  if(true){
		    	  LCD_Printf("Rien");
		    	  //avance et continue le mega loop
		    	  avancerDroit();
			      THREAD_MSleep(250);
		    	  }else{
		    		  rectification = true;
		    		  if(totalVirageDroite > 0){
		    			  LCD_ClearAndPrint("Droite");
		    			  		    	  deviation(-100);
		    			  		    	  totalVirageDroite--;
		    			  			      THREAD_MSleep(250);
		    			  		    	  //deviation(100);
		    		  }else{
		    			  LCD_ClearAndPrint("Gauche");
		    			 		    	  deviation(100);
		    			 		    	  totalVirageDroite++;
		    			 			      THREAD_MSleep(250);
		    			 		    	  //deviation(-100);
		    		  }
		    		  if(totalVirageDroite == 0)
		    			  rectification = false;
		    	  }
		      }
		      else if(IRgauche && !IRdroite)
		      {
		    	  LCD_ClearAndPrint("Gauche");
		    	  deviation(100);
		    	  totalVirageDroite++;
			      THREAD_MSleep(250);
		    	  deviation(-100);

		      }
		      else if(IRdroite && !IRgauche)
		      {
		    	  LCD_ClearAndPrint("Droite");
		    	  deviation(-100);
		    	  totalVirageDroite--;
			      THREAD_MSleep(250);
		    	  deviation(100);
		      }
		      else // 2 dÈtecteurs activÈs
		      {
		    	  LCD_ClearAndPrint("Deux");
		    	  deviation(100);
		    	  totalVirageDroite++;
			      THREAD_MSleep(250);
		    	  deviation(-100);
		      }
			}
  }
}
void surLeVert(){
	 level = 2;
}
void getColorThread(){
	while(1){
	currentColor = readAndGetColor(unRobot.estRobot43);
	}
}
void parcours(robot &unRobot, short int OverrideFrequencyStart)
{
	//Verifie quel est le ROBOT en cours!
	unRobot.estRobot43 = DIGITALIO_Read(9);
	bool premierePasse = true;
	bool premierSonEffectuer = false;
	bool IRgauche=false;
	bool IRdroite=false;
	int couleur=0;
	int sortie=0;

	LCD_Printf("lol0\n");
	if(unRobot.estRobot43)
		initCapteurI2C();

	int timer1=0,tempsDeTournage;  //Pour la dÈtection dobjet en avant, Pour le temps a tourner
	bool cannette=false;
	LCD_Printf("lol1\n");

	//DEPART DES THREADS
	THREAD thread_frequence, thread_couleur;
	LCD_Printf("lol2\n");
	thread_frequence = THREAD_CreateSimple(detectionFrequence);
	LCD_Printf("lol3\n");

	if(OverrideFrequencyStart==1)
	{
		depart14=true;
		depart43=true;
	}
	LCD_Printf("\nARRET: %i %i\n",arret?1:0,true?1:0);

	while (!arret) // Thread detectionFrequence gere l'arret du programme.
	{
		//METHODE 1 : Les 2 robots utilisent la meme technique sur le parcours
		if (depart14||depart43)
		{
			if(premierePasse)
			{
				avancerDroit();
				premierePasse=false;
			}
			//----------------------------------------------
			//-------------Detection Couleur----------------
			//----------------------------------------------
			switch(readAndGetColor(unRobot.estRobot43))
			{
				case 0:
					//LCD_Printf("BLANC");break;
					break;
				case 1:
					LCD_Printf("BLEU");
					//arret=true;
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


                      	//DUDE jfais une nouvelle methode de parcours en haut



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
              /*
              		int vitesseDroit = getContraste() > 220 ? 80 : 100;
              		int vitesseGauhe = getContraste() <= 220 ? 100 : 80;*/
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
					LCD_Printf("VERT");
					//arret=true;
					break;
				case 4:
					LCD_Printf("JAUNE");
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
					//avance si rien de spÈcial
					avancerDroit();

			}
			else if(IRgauche==true && IRdroite == false && timer1 != 0)
			{
				//dÈvie vers la droite si obstacle trouvÈ
				//***Pas sure que le robot dÈtecte comme faut juste 1 capteur
				MOTOR_SetSpeed(7,100);
				MOTOR_SetSpeed(8,80);
			}
			else if(IRdroite==true && IRdroite == false && timer1 != 0)
			{
				//dÈvie vers la gauche si obstacle trouvÈ
				//***Pas sure que le robot dÈtecte comme faut juste 1 capteur
				MOTOR_SetSpeed(7,80);
				MOTOR_SetSpeed(8,100);
			}
			else // 2 dÈtecteurs activÈs
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
					//pendant 1 secondes! Pas plus compliquÈ que ca sinon ca chie
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
	}

	//Stop les moteurs
	MOTOR_SetSpeed(7,0);
	MOTOR_SetSpeed(8,0);

	LCD_ClearAndPrint("FINI");

}


void avancerDroit()
{
	if(unRobot.estRobot43) //Si bool unRobot.estRobot43;
	{
		MOTOR_SetSpeed(7,left43);
		MOTOR_SetSpeed(8,right43);
	}
	else
	{
		MOTOR_SetSpeed(7,left14);
		MOTOR_SetSpeed(8,right14);
	}
}
void reculerDroit()
{
	if(unRobot.estRobot43) //Si bool unRobot.estRobot43;
	{
		MOTOR_SetSpeed(7,-left43);
		MOTOR_SetSpeed(8,-right43);
	}
	else
	{
		MOTOR_SetSpeed(7,-left14);
		MOTOR_SetSpeed(8,-right14);
	}
}



//la deviation droite c'est un chiffre (max 100). cest mega bs mais ca marche.
void deviation(int deviationDroite)
{
    deviationDroite = deviationDroite / 2.5;
	if(deviationDroite>=0){
		MOTOR_SetSpeed(MOTOR_LEFT,100);
		MOTOR_SetSpeed(MOTOR_RIGHT,100-deviationDroite);
	}else{
		MOTOR_SetSpeed(MOTOR_LEFT,100+deviationDroite);
		MOTOR_SetSpeed(MOTOR_RIGHT,100);
	}

}
//la deviation droite c'est un chiffre (max 100). cest mega bs mais ca marche.
void reverseDeviation(int deviationDroite)
{
    deviationDroite = deviationDroite / 2.5;
	if(deviationDroite>=0){
		MOTOR_SetSpeed(MOTOR_LEFT,-100+deviationDroite);
		MOTOR_SetSpeed(MOTOR_RIGHT,-100);
	}else{
		MOTOR_SetSpeed(MOTOR_LEFT,-100);
		MOTOR_SetSpeed(MOTOR_RIGHT,-100+deviationDroite);
	}

}
void atteintLeBleu()
{
	THREAD_MSleep(50);
	MOTOR_SetSpeed(MOTOR_LEFT,0);
	MOTOR_SetSpeed(MOTOR_RIGHT,0);

	while(currentColor == BLUE_COLOR)
	{
		//tout est goooooood
		THREAD_MSleep(100);
	}

	//FUCK FAUT REPRENDRE LE BLEU.
	level = 2;
}
//mÈthode qui termine seulement quand la bonne frÈquence est entendue. le fait sans msleep pour que ca soit le plus rapide (ya rien de fait en parallËle ‡ Áa anyway)
void detectionStartFrequence()
{
	LCD_Printf("DÈmarre detection start\n");
	bool etatFrequence = false;
	bool initTemps= false;
	bool premierSonEffectuer = false;
	int duree5khz=0;
	int temps = 0;
  	bool shouldGo = false;

	//on choisit le bon mode de gestion d'erreur
	ERROR_SetMode(LCD_ONLY);
  	while(!shouldGo)
	{
		bool etatFrequence = DIGITALIO_Read(10);

		//LCD_ClearAndPrint("valeur1=%d/n",duree5khz);
		if(etatFrequence==1 && initTemps == false)
		{
			initTemps = true;
			temps = SYSTEM_ReadTimerMSeconds();
			LCD_Printf("inittemps");
		}

		duree5khz=SYSTEM_ReadTimerMSeconds() - temps;
		if (duree5khz > 500 && initTemps && etatFrequence == 1)
			break;

		if (etatFrequence==0 && initTemps == true)
		{
			initTemps = false;
			LCD_Printf("falldown");

			if (duree5khz > 100)//(duree5khz < 2100 && duree5khz > 1900)
			{
				//Ecrire la fonction qui fait avancer le robot
				if(premierSonEffectuer == false)
				{
					if(unRobot.estRobot43 == false)
					{
						premierSonEffectuer = true;
                        shouldGo = true;
					}
					else
						premierSonEffectuer = true;
				}
				else if(premierSonEffectuer == true && unRobot.estRobot43 == true)
				{
                    shouldGo = true;
				}
			}
				temps = 0;
		}
	}
}

//Sert a† gerer le depart et l'arret du ou des programmes en fonction de la duree du 5kHz,
//La surveillance du signal se fait en temps reel et sans AUCUN MSLEEP !!!! <--- not good
void detectionFrequence()
{
	LCD_Printf("DÈmarre detection");

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

			if (duree5khz > 3200)
			{
				gameOver();
			}
				temps = 0;
		}
      	//pour laisser le CPU relaxer un peu pour faire d'autre choses utiles
		THREAD_MSleep(400);
	}
}

void gameOver(){
					//shutdown toute. game over
					//LCD_Printf("\nshutdown");
					//Stop les moteurs
					MOTOR_SetSpeed(7,0);
					MOTOR_SetSpeed(8,0);
					FPGA_StopAll();
					LCD_PrintBmp("genius.bmp");
					exit(0);
}



