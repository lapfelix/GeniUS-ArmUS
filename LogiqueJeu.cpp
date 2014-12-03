#include "LogiqueJeu.h"

pthread_t thread_scan;

void createThread(&Robot);
void mainLoop(&Robot);

void startGame(Robot &unRobot){
	createThread(&unRobot);

	while(unRobot.getCurrentButton() != BOUTON_BLEU && readAndGetColor() != GREEN_COLOR){
		THREAD_MSleep(50);
	}

	//rentre dans le main loop
	mainLoop(&unRobot);
}

void mainLoop(Robot &unRobot){

}

void createThread(Robot &unRobot){
	THREAD_Create(&thread_scan,&Robot::scanPointer,&unRobot);
}
