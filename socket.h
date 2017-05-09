/* Classe permettant la communication entre le robot et l'application */

#ifndef __SOCKET__
#define __SOCKET__

// Librairies
#include <string>
#include <iostream>

// Librairies socket
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#define closesocket(param) close(param)
#define INVALID_SOCKET -1
#define SOCKET_ERROR -1

#define MODE PF_INET

typedef int SOCKET;
typedef struct sockaddr_in SOCKADDR_IN;
typedef struct sockaddr SOCKADDR;

class Socket
{
	SOCKET sock, csock;
	int port;
	public: 	// Méthodes publiques
		Socket(int);
		~Socket();
		std::string getOrder();
		void initSocket();
		void killSocket();
};

#endif
