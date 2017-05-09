#include "socket.h"

using namespace std;

Socket::Socket(int port)
{
	this->port = port;
}
void Socket::initSocket()
{
	// Socket serveur
	SOCKADDR_IN sin;
	socklen_t recsize = sizeof(sin);

	// Socket pour le client
	SOCKADDR_IN csin;
	socklen_t crecsize = sizeof(csin);

	int sock_err;
	this->sock = socket(MODE, SOCK_STREAM, 0);
	int opt = 1;
	setsockopt(this->sock, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

	if(this->sock != INVALID_SOCKET) {
		// Configuration du socket serveur
		sin.sin_addr.s_addr = htonl(INADDR_ANY);	// @ IP automatique
		sin.sin_family = MODE;
		sin.sin_port = htons(this->port);			// port d'écoute
		sock_err = bind(this->sock, (SOCKADDR*)&sin, recsize);

		if(sock_err != SOCKET_ERROR) {	// si le socket fonctionne
			int l = listen(this->sock, 0);
			if(l != SOCKET_ERROR) {
				cout<<"Attente de connexion du client Android sur le port "<<this->port<<" ..."<<endl;
				this->csock = accept(sock, (SOCKADDR*) &csin, &crecsize);
				cout<<"Connexion détectée "<<this->csock<<" - @IP : "<<inet_ntoa(csin.sin_addr)<<":"<<htons(csin.sin_port)<<endl;
			}
		}
		else {
			cout<<"Erreur socket 2 (sock_err : "<<sock_err<<" - errno : "<<strerror(errno)<<")"<<endl;
		}
	}
	else {
		cout<<"erreur socket 1"<<endl;
	}
}
void Socket::killSocket()
{
	if((this->csock != SOCKET_ERROR) || (this->csock != INVALID_SOCKET)) {
		shutdown(this->csock, 2);
		closesocket(this->csock);
	}
	if((this->sock != SOCKET_ERROR) || (this->sock != INVALID_SOCKET)) {
		shutdown(this->sock, 2);
		closesocket(this->sock);
	}
}
string Socket::getOrder()
{
	char buffer[128] = "";
	string ret;
	int err = recv(this->csock, buffer, (sizeof(buffer) + 1), 0);
	if(err != SOCKET_ERROR) {
		ret = buffer;
	}
	else {
		ret = "ERR-TRANSMISSION";
	}
	return ret;
}
Socket::~Socket()
{
	
}
