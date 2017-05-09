#include <iostream>
#include <string>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#define INVALID_SOCKET -1
#define SOCKET_ERROR -1
#define closesocket(s) close(s)
typedef int SOCKET;
typedef struct sockaddr_in SOCKADDR_IN;
typedef struct sockaddr SOCKADDR;

using namespace std;

int main(int argc, char** argv)
{
	cout<<"Client permettant de tester le serveur sur la Rpi"<<endl;
	// gestion des paramètres
	if(argc != 3) {
		cout<<"Usage : [ip] [port]"<<endl;
		return -1;
	}

	string ip = argv[1];
	int port = atoi(argv[2]);

	cout<<"IP : "<<ip<<endl;
	cout<<"Port : "<<port<<endl;


	SOCKET sock;
	SOCKADDR_IN sin;

	sock = socket(AF_INET, SOCK_STREAM, 0);
	sin.sin_addr.s_addr = inet_addr(ip.c_str());
	sin.sin_family = PF_INET;
	sin.sin_port = htons(port);
	int c = connect(sock, (SOCKADDR*) &sin, sizeof(sin));

	if(c != SOCKET_ERROR) {
		string msg;
		cout<<"Connexion valide avec la Raspberry Pi ("<<inet_ntoa(sin.sin_addr)<<":"<<htons(sin.sin_port)<<")"<<endl;
		do {
			cout<<"rosetta $ ";
			cin>>msg;
			cout<<"Transmission au robot ... ";
			int err = send(sock, msg.c_str(), (msg.size() + 1), 0);
			if(err != SOCKET_ERROR) {
				cout<<"Envoyé !"<<endl;
			}
			else {
				cout<<"Erreur"<<endl;
			}
			if(msg == "halt") {
				cout<<"Arrêt du logiciel embarqué"<<endl;
				msg = "exit";	// pour sortir de la boucle
			}
		}
		while(msg != "exit");
	}
	else {
		cout<<"Le robot n'est pas en ligne"<<endl;
	}
	closesocket(sock);
	return 0;
}
