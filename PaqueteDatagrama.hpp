#ifndef DATAGRAM_H_
#define DATAGRAM_H_

#include <cstddef>
#include <string>
#include <vector>

class PaqueteDatagrama{
	private:
		std::vector<char> datos;		
		std::string ip;
		uint16_t puerto;	
	public:
		PaqueteDatagrama(char *datos, std::size_t tamanio, std::string ip, uint16_t puerto);
		PaqueteDatagrama(std::size_t tamanio);
		~PaqueteDatagrama(void);
		void *obtieneDatos(void);
		std::vector<char> &obtieneVectorDatos();
		void inicializaDatos(char*,std::size_t);
		std::size_t obtieneLongitud(void);
		void inicializaIP(std::string ip);
		std::string obtieneIP(void);
		uint16_t obtienePuerto(void);
		void inicializaPuerto(uint16_t puerto);		
};

#endif
