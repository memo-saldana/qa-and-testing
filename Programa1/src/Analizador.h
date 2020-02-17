#pragma once
#include <string>
#include <cctype>
#include "Lector.h"
using namespace std;
class Analizador
{
private:
    int blanco, comentarios, codigo;
    string archivoAnalizado;
    bool lineaEnBlanco(string linea);
public:
    Analizador();
    void contarLineas(Lector &lector);
    void imprimir();
};

Analizador::Analizador()
{
    blanco = 0;
    comentarios = 0;
    codigo = 0;
    archivoAnalizado = "";
}

void Analizador::contarLineas(Lector &lector)
{
    string linea;
    bool inMultilineComment = false;
    this->archivoAnalizado = lector.getNombre();

    while (!lector.fin())
    {   
        linea = lector.getSigLinea();
        if (inMultilineComment)
        {
            comentarios++;
            if (linea.find("*/") != -1)
            {
                inMultilineComment = false;
            }
        }
        else
        {
            if (linea.find("//") != -1)
            {
                comentarios++;
            }
            else if (linea.find("/*") != -1)
            {
                comentarios++;
                inMultilineComment = true;
            }
            else if (lineaEnBlanco(linea))
            {
                blanco++;
            }
            else
            {
                codigo++;
            }
        }
    }
}

void Analizador::imprimir()
{
    cout<<"Nombre del archivo: "<< archivoAnalizado <<endl;
    cout<<"--------------------------------------------"<<endl;
    cout<<"Cantidad de líneas en blanco: "<< blanco <<endl;
    cout<<"Cantidad de líneas en comentarios: "<< comentarios <<endl;
    cout<<"Cantidad de líneas en código: "<< codigo <<endl;
    cout<<"--------------------------------------------"<<endl;
    cout<<"Cantidad total de líneas: "<< blanco + comentarios + codigo <<endl;
}

bool Analizador::lineaEnBlanco(string linea)
{
    for(char caracter : linea) {
        if(!isspace(caracter)) {
            return false;
        }
    }
    return true;
}


