#include "ultrasonic.h"

using namespace std;

UltraSonic::UltraSonic(string pos)
{
	this->pos = pos;
	cout<<"Initialisation du capteur "<<this->pos<<" ... ";
	this->trigger = 29;	// la broche trigger est commune aux deux capteurs (ils ne fonctionnent pas en même temps, on peut déclencher l'autre sans problème
	if(this->pos == "AV") {		// définition des broches du capteur
		this->echo = 4;
	}
	else {
		this->echo = 31;
	}
	cout<<"Fait !"<<endl;
}
double UltraSonic::getDistance()
{
	stringstream sstm;
	sstm << "python /home/pi/distance.py " << this->trigger<<" "<<this->echo;
	string append = sstm.str();

	FILE *fp;
	char v[1035];

	fp = popen(append.c_str(), "r");
	if (fp == NULL) {
		printf("Failed to run command\n" );
		exit(1);
	}

	string value = "";
	while (fgets(v, sizeof(v)-1, fp) != NULL) {
		value += v;
 	}
 	
	pclose(fp);
	double distance;
	distance = stod(value);
	cout<<"Distance en sortie du capteur : "<<distance<<endl;
	return distance;
}
string UltraSonic::intToString(int value)
{
	return "";
}
string UltraSonic::getPos()
{
	return this->pos;
}
