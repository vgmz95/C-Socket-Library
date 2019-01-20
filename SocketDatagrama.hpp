#ifndef SOCKETD_H
#define SOCKETD_H

#include <netinet/in.h>
#include <sys/time.h>
#include "PaqueteDatagrama.hpp"

class SocketDatagrama {
	private:
		struct sockaddr_in direccionLocal;
		int s;
		bool timeout;
		
	public:
		SocketDatagrama(uint16_t);
		~SocketDatagrama(void);
		int recibe(PaqueteDatagrama& p);
		int envia(PaqueteDatagrama& p);
		
		void setTimeout(time_t segundos, suseconds_t microsegundos);
		void unsetTimeout(void);
		void setBroadcast(int);				
		
		bool haExpirado(void);		
		void cerrarConexion(void);		
};

#endif
