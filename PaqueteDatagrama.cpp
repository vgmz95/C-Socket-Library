#include"PaqueteDatagrama.hpp"

PaqueteDatagrama::PaqueteDatagrama(char* datos, std::size_t tamanio, std::string ip, uint16_t puerto) {
	this->datos = std::vector<char> (datos, datos + tamanio); 
	this->ip=ip;
	this->puerto=puerto;
}

PaqueteDatagrama::PaqueteDatagrama(std::size_t tamanio) {
	this->datos = std::vector<char> (tamanio); 
}

PaqueteDatagrama::~PaqueteDatagrama(){this->datos.clear();}

std::size_t PaqueteDatagrama::obtieneLongitud(){return this->datos.size();}

void* PaqueteDatagrama::obtieneDatos(){return this->datos.data();}

std::vector<char>& PaqueteDatagrama::obtieneVectorDatos(){return this->datos;}

void PaqueteDatagrama::inicializaDatos(char* datos, std::size_t tamanio) {this->datos = std::vector<char> (datos, datos + tamanio); }
	
void PaqueteDatagrama::inicializaIP(std::string ip){this->ip=ip;}

std::string PaqueteDatagrama::obtieneIP(void){return ip;}

uint16_t PaqueteDatagrama::obtienePuerto(void){return puerto;}

void PaqueteDatagrama::inicializaPuerto(uint16_t puerto){ this->puerto=puerto;}
