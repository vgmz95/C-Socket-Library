#include "SocketDatagrama.hpp"

#include <iostream>
#include <cstring>

#include <unistd.h>
#include <arpa/inet.h>

SocketDatagrama::SocketDatagrama(uint16_t p) {
	s = socket(AF_INET, SOCK_DGRAM, 0);
	if (s == -1){
		std::cerr << "Error al crear el socket: "<<strerror(errno) << std::endl;
		exit(0);
	}
	bzero((char *)&direccionLocal, sizeof(direccionLocal));
	direccionLocal.sin_family = AF_INET;
	direccionLocal.sin_addr.s_addr = INADDR_ANY;
	direccionLocal.sin_port = htons(p);
	timeout=false;
	
	if (bind(s, (struct sockaddr *)&direccionLocal, sizeof(direccionLocal)) == -1){
		std::cerr << "Error en el bind: "<<strerror(errno) << std::endl;
	}
	return;	
}

SocketDatagrama::~SocketDatagrama() { close(s); }
	
void SocketDatagrama::cerrarConexion() { close(s); }


int SocketDatagrama::recibe(PaqueteDatagrama &p) {
	int tam;
	struct sockaddr_in direccionForeanea;
	socklen_t n = sizeof(direccionForeanea);
	memset(p.obtieneDatos(),'\0',p.obtieneLongitud());	
	//Recibe datos
	if ((tam = recvfrom(s, p.obtieneDatos(), p.obtieneLongitud(), 0,(struct sockaddr *)&direccionForeanea, &n)) == -1){
		if(errno==EAGAIN||errno==EWOULDBLOCK){//Expiro el socket
			std::cerr << "Socket Timeout. "<< std::endl;
			timeout=true;
		}else{//Otro tipo de error
			std::cerr << "Error al recibir el mensaje: "<<strerror(errno) << std::endl;
			timeout=false;
		}
	}else{//Ningun error
		p.inicializaIP(std::string(inet_ntoa(direccionForeanea.sin_addr)));
		p.inicializaPuerto(htons(direccionForeanea.sin_port));
		timeout=false;
	}
			
	unsetTimeout();
	return tam;	
}

int SocketDatagrama::envia(PaqueteDatagrama &p) {
	//Inicializacion de la direccion del host remoto
	struct sockaddr_in direccionForeanea;
	memset(&direccionForeanea,0,sizeof direccionForeanea);
	direccionForeanea.sin_family = AF_INET;
	direccionForeanea.sin_addr.s_addr = inet_addr(p.obtieneIP().c_str());
	direccionForeanea.sin_port = htons(p.obtienePuerto());

	int tam;
	//Envio de datos
	if ((tam = sendto(s,p.obtieneDatos(),p.obtieneLongitud(), 0,(struct sockaddr *)&direccionForeanea,sizeof(direccionForeanea))) == -1)
		std::cerr << "Error al enviar el mensaje: "<<strerror(errno) << std::endl;
	//Retorno de la longitud enviada
	return tam;
}

void SocketDatagrama::setTimeout(time_t segundos, suseconds_t microsegundos){	
	struct timeval timeout;      
    timeout.tv_sec = segundos;
    timeout.tv_usec = microsegundos;		
    if (setsockopt (s, SOL_SOCKET, SO_RCVTIMEO, (char *)&timeout,sizeof(timeout)) < 0){
        std::cerr << "Error en el setTimeout: "<<strerror(errno) << std::endl;
    }
}

void SocketDatagrama:: unsetTimeout(){setTimeout(0,0);}
		
void SocketDatagrama:: setBroadcast(int yes){
	if(setsockopt(s,SOL_SOCKET,SO_BROADCAST,&yes,sizeof(int)) == -1)
		std::cerr << "Error al activar la opción multicast del socket: "<<strerror(errno) << std::endl;
}

	
bool SocketDatagrama::haExpirado(){return timeout;}

