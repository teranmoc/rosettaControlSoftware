/* Classe permettant de mouvoir le robot */

#ifndef __ROBOT__
#define __ROBOT__

// Librairies
#include <string>
#include <iostream>
#include <unistd.h>
#include "wiringPi.h"
#include <softPwm.h>
#include <cstdlib>

enum MOTOR { ARD, ARG, AVD, AVG };
enum PIN_TYPE { PWM, IN1, IN2 };

class Robot
{
	int** pins;
	int nbMotors;
	bool progressive;	// mode de démarrage des moteurs progressif (jusqu'à la vitesse) ou directement à la consigne
	private:	// Méthodes privées
		void startMotor(int, bool, int);
		void stopMotor(int);
	public: 	// Méthodes publiques
		Robot(int, bool);
		void avancer(int speed = 100);
		void reculer(int speed = 100);
		void gauche(bool, bool, int speed = 100);
		void droite(bool, bool, int speed = 100);
		void stop();
};

#endif
