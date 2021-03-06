#pragma once
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class Lector
{
private:
    fstream archivo;
    string nombre;
public:
    bool fin();
    string getNombre();
    string getSigLinea();
    Lector();
    ~Lector();
};

//.i
Lector::Lector()
{
    string nombrePotencial;

    cout<<"Teclee el nombre del archivo junto con su terminación. (.txt, .cpp, .h, etc.)"<<endl;
    getline(cin, nombrePotencial);

    if (nombrePotencial == "")
    {
        throw runtime_error("Error de verificación: El nombre del archivo no puede estar vacío");
    }

    nombre = nombrePotencial;
    archivo.open(nombre);

    if (!archivo)
    {
        throw runtime_error("Error de verificación: No existe un archivo con ese nombre");
    }

    if (archivo.peek() == std::ifstream::traits_type::eof())
    {
        throw runtime_error("Error de verificación: El archivo no puede estar vacío");
    }
}

//.i
Lector::~Lector()
{
    archivo.close();
}

//.i
bool Lector::fin()
{
    return archivo.eof();
}

//.i
string Lector::getNombre()
{
    return this->nombre;
}

//.i
string Lector::getSigLinea()
{
    string linea;
    getline(archivo, linea);
    return linea;
}
