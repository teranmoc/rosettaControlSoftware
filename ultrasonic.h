/* Classe permettant l'utilisation des deux capteurs ultrason */

#ifndef __ULTRASONIC__
#define __ULTRASONIC__

// Librairies
#include <string>
#include <iostream>
#include <sstream>

#include "wiringPi.h"

class UltraSonic
{
	
	std::string pos;
	int trigger;
	int echo;
	private:	// Méthodes privées
		std::string intToString(int);
	
	public: 	// Méthodes publiques
		UltraSonic(std::string);
		double getDistance();
		std::string getPos();
};

#endif
