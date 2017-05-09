#include "robot.h"

using namespace std;

Robot::Robot(int nbMotors, bool progressive)
{
	cout<<"Initialisation du robot ... ";	
	this->nbMotors = nbMotors;
	this->progressive = progressive;

	// initialisation des pins
	try // Méthode dynamique
	{
		
		this->pins = new int* [this->nbMotors];
		for(int i = 0; i < this->nbMotors; i++) {this->pins[i] = new int [3]; }
	}
	catch (const std::bad_alloc &) // erreur d'allocation
	{
		// désallouer tout ce qui a été alloué avec succès
		cout<<"Erreur d'allocation"<<endl;
		for(int i = 0; i < 4; i++ ) 
			delete []this->pins[i];
		delete [] this->pins;
		exit(4); // arret du programme
	}

	// définition des pins
	this->pins[ARD][PWM] = 6;
	this->pins[ARD][IN1] = 10;
	this->pins[ARD][IN2] = 11;

	this->pins[ARG][PWM] = 12;
	this->pins[ARG][IN1] = 13;
	this->pins[ARG][IN2] = 14;

	this->pins[AVD][PWM] = 1;
	this->pins[AVD][IN1] = 4;
	this->pins[AVD][IN2] = 5;

	this->pins[AVG][PWM] = 0;
	this->pins[AVG][IN1] = 2;
	this->pins[AVG][IN2] = 3;

	wiringPiSetup();
	for(int i = ARD; i <= AVG; i++) {
		pinMode(this->pins[i][PWM], OUTPUT);
		pinMode(this->pins[i][IN1], OUTPUT);
		pinMode(this->pins[i][IN2], OUTPUT);
		softPwmCreate(this->pins[i][PWM], 0, 100);
	}
	cout<<"Fait !"<<endl;
	if(this->progressive) {
		cout<<"Le mode progressif est actif"<<endl;
	}
}
void Robot::avancer(int speed)
{
	this->startMotor(ARD, true, speed);
	this->startMotor(ARG, true, speed);
	this->startMotor(AVD, true, speed);
	this->startMotor(AVG, true, speed);
}
void Robot::reculer(int speed)
{
	this->startMotor(ARD, false, speed);
	this->startMotor(ARG, false, speed);
	this->startMotor(AVD, false, speed);
	this->startMotor(AVG, false, speed);
}
void Robot::gauche(bool type, bool direction, int speed)
{
	if(type) {
		this->startMotor(ARG, false, speed);
		this->startMotor(AVG, false, speed);
		this->startMotor(ARD, true, speed);
		this->startMotor(AVD, true, speed);
	}
	else {
		if(direction) {		// Avant gauche
			this->stopMotor(ARG);
			this->stopMotor(AVG);
			this->startMotor(ARD, true, speed);
			this->startMotor(AVD, true, speed);
		}
		else {			// Arrière gauche
			this->stopMotor(ARG);
			this->stopMotor(AVG);
			this->startMotor(ARD, false, speed);
			this->startMotor(AVD, false, speed);
		}
	}
}
void Robot::droite(bool type, bool direction, int speed)
{
	if(type) {
		this->startMotor(ARG, true, speed);
		this->startMotor(AVG, true, speed);
		this->startMotor(ARD, false, speed);
		this->startMotor(AVD, false, speed);
	}
	else {
		this->stopMotor(ARD);
		this->stopMotor(AVD);
		if(direction) {		// Avant droite
			this->startMotor(ARG, true, speed);
			this->startMotor(AVG, true, speed);
		}
		else {			// Arrière droite
			this->startMotor(ARG, false, speed);
			this->startMotor(AVG, false, speed);
		}
	}
}
void Robot::stop()
{
	this->stopMotor(ARD);
	this->stopMotor(ARG);
	this->stopMotor(AVD);
	this->stopMotor(AVG);
}

// Méthodes privées

// Fait fonctionner le moteur indiqué en paramètre (var : motor), selon le sens (var : front) et la vitesse (var : speed)
void Robot::startMotor(int motor, bool front, int speed)
{
	if(front) {
		digitalWrite(this->pins[motor][IN1], 1);
		digitalWrite(this->pins[motor][IN2], 0);
	}
	else {		
		digitalWrite(this->pins[motor][IN1], 0);
		digitalWrite(this->pins[motor][IN2], 1);
	}
	softPwmWrite(this->pins[motor][PWM], speed);
	/*if(this->progressive) {		// en mode progressif, le robot effectue les mouvements en douceur
		softPwmWrite(this->pins[motor][PWM], 20);
		sleep(5);
		softPwmWrite(this->pins[motor][PWM], 40);
		sleep(5);
		softPwmWrite(this->pins[motor][PWM], 60);
		sleep(5);
		softPwmWrite(this->pins[motor][PWM], 80);
		sleep(5);
		softPwmWrite(this->pins[motor][PWM], 100);
	}
	else {						// le robot démarre directement à sa vitesse max
		softPwmWrite(this->pins[motor][PWM], speed);
	}//*/
}
void Robot::stopMotor(int motor)
{
	digitalWrite(this->pins[motor][IN1], 0);
	digitalWrite(this->pins[motor][IN2], 0);
	softPwmWrite(this->pins[motor][PWM], 0);
}
