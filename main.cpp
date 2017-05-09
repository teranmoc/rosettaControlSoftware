/*
Logiciel permettant uniquement le contrôle des déplacements du robot via une application Android
UCE : Application Systèmes Embarqués
UE : Systèmes Embarqués

Auteur : Jérémie Décome
Mise à jour : 02/01/2017
*/
#include <thread>

#include "robot.h"
#include "socket.h"
#include "ultrasonic.h"

using namespace std;

// Variables globales
string order = "";
double d = 0;


// Méthodes threadés
void communicate(Socket s) {		// lecture de la socket
	while((order != "exit") && (order != "halt")) {
		order = s.getOrder();
		cout<<"[Thread] Ordre reçu : "<<order<<" - thread en attente"<<endl;
	}
	cout<<"Arrêt du thread"<<endl;
}

void checkDistance(UltraSonic us) {	// lecture du capteur passé en paramètre, déclenché par un timer lorsqu'on en a besoin
	while(true) {
		d = us.getDistance();
		//usleep(1000);		// attente de 1 s entre deux itérations (car le script Python demande du temps à s'exécuter)
	}
}

int main(void)
{
	cout<<"Logiciel embarqué du robot"<<endl;
	Robot r(4, true);
	string pc;
	Socket s(2155);
	UltraSonic av("AV"), ar("AR");
	while(true) {
		s.initSocket();
		thread com(communicate, s);
		//thread checkAV(checkDistance, av);
		//thread checkAR(checkDistance, av);
		while(order != "exit") {		
			if(order.find("A") != string::npos) {		// le robot doit avancer mais tout droit ou à gauche ?
				if(order.substr(1, 1) == "G") {
					r.gauche(false, true, atoi(order.substr(2, 3).c_str()));
				}
				else if(order.substr(1, 1) == "D") {
					r.droite(false, true, atoi(order.substr(2, 3).c_str()));
				}
				else {
					if(av.getDistance() < 40) {		// vu que la lecture du socket est threadé, le main peut traiter la distance (d => av.getDistance())
						r.stop();
					}
					else {
						r.avancer(atoi(order.substr(1, 3).c_str()));	// On récupère le % et on envoi
					}
				}
				
				
			}
			else if(order.find("R") != string::npos) {
				if(order.substr(1, 1) == "G") {
					r.gauche(false, false, atoi(order.substr(2, 3).c_str()));
				}
				else if(order.substr(1, 1) == "D") {
					r.droite(false, false, atoi(order.substr(2, 3).c_str()));
				}
				else {
					if(ar.getDistance() < 40) {		// vu que la lecture du socket est threadé, le main peut traiter la distance (d => av.getDistance())
						r.stop();
					}
					else {
						r.reculer(atoi(order.substr(1, 3).c_str()));	// On récupère le % et on envoi
					}
				}
				
			}
			else if(order.find("G") != string::npos) {
				r.gauche(true, true, atoi(order.substr(1, 3).c_str()));
			}
			else if(order.find("D") != string::npos) {
				r.droite(true, true, atoi(order.substr(1, 3).c_str()));
			}
			else if(order == "stop") {
				r.stop();
			}
			else if(order == "halt") {
				com.detach();
				r.stop();
				s.killSocket();
				return 0;
			}
			else {
			}
		}
		r.stop();
		com.detach();
		s.killSocket();
		order = "";
	}
	return 0;
}
