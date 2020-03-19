#pragma once
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

//.b=37

class Lector {
private:
    fstream archivo;
    string nombre;
public:
    bool fin();
    string getNombre();
    string getSigLinea();
    bool abrir(string nombre);
    ~Lector();
};

//.i
bool Lector::abrir(string nombre) {
    archivo.open(nombre);

    if (!archivo) {
        cout<<"No existe un archivo con el nombre \""<< nombre <<  "\". Intente nuevamente.\n";
        return false;
    }

    if (archivo.peek() == std::ifstream::traits_type::eof()) {
        cout<<"El archivo con nombre \""<< nombre <<  "\" esta vacio, no se analizara.\n";
        return false;
    }

	this->nombre = nombre;
    return true;
}

//.i
Lector::~Lector() {
    archivo.close();
}

//.i
bool Lector::fin() {
    return archivo.eof();
}

//.i
string Lector::getNombre() {
	int i = this->nombre.find(".");
	if(i == -1) return nombre;
    return this->nombre.substr(0,i);
}

//.i
string Lector::getSigLinea() {
    string linea;
    getline(archivo, linea);
    return linea;
}
