#include"PaqueteDatagrama.hpp"
#include <cstring>

PaqueteDatagrama::PaqueteDatagrama(char* data, std::size_t tamanio, std::string ip, uint16_t puerto) {
	datos = new char[tamanio];
	memcpy(datos,data, tamanio);
	this->tamanio=tamanio;
	this->ip=ip;
	this->puerto=puerto;
}

PaqueteDatagrama::PaqueteDatagrama(std::size_t tamanio) {
	datos = new char[tamanio];
	this->tamanio=tamanio;
}

PaqueteDatagrama::~PaqueteDatagrama(){delete[] datos;}

std::size_t PaqueteDatagrama::obtieneLongitud(){return tamanio;}

void* PaqueteDatagrama::obtieneDatos(){return datos;}

void PaqueteDatagrama::inicializaDatos(char* d) {memcpy(datos, d, tamanio);}
	
void PaqueteDatagrama::inicializaIP(std::string ip){this->ip=ip;}

std::string PaqueteDatagrama::obtieneIP(void){return ip;}

uint16_t PaqueteDatagrama::obtienePuerto(void){return puerto;}

void PaqueteDatagrama::inicializaPuerto(uint16_t puerto){ this->puerto=puerto;}
