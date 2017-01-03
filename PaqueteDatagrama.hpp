#ifndef DATAGRAM_H_
#define DATAGRAM_H_
#include <cstddef>
#include <string>

class PaqueteDatagrama{
	private:
		char *datos;		
		std::size_t tamanio;
		std::string ip;
		uint16_t puerto;	
	public:
		PaqueteDatagrama(char *datos, std::size_t tamanio, std::string ip, uint16_t puerto);
		PaqueteDatagrama(std::size_t);
		~PaqueteDatagrama(void);
		void *obtieneDatos(void);
		void inicializaDatos(char*);
		std::size_t obtieneLongitud(void);
		void inicializaIP(std::string ip);
		std::string obtieneIP(void);
		uint16_t obtienePuerto(void);
		void inicializaPuerto(uint16_t puerto);		
};

#endif
