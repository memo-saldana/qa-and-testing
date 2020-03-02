#include <iostream>
#include <fstream>
#include <vector>
#include "Lector.h"
#include "Parte.h"
#include "Analizador.h"
using namespace std;

//.b=9

//.i
void imprimir(vector<Parte> partes) {
    if(partes.size() == 0) {
        cout<<"No hay partes registradas, no se pudo generar reporte, intente tecleando nombres de archivos existentes.\n";
        return;
    }
    ofstream salida;
    salida.open("ConteoLDC.txt");
    int total = 0;
    cout<<"PARTES BASE:\n";
    salida<<"PARTES BASE:\n";
    for(auto parte: partes) {
        if(parte.esBase()) {
            total+=parte.getTotal();
            cout<<"\t"<<parte.getNombre()<<":\tT="<<parte.getTotal()<<",\tI="<<parte.getItems()<<",\tB="<<parte.getBase()<<",\tD="<<parte.getBorradas()<<",\tM="<<parte.getModificadas()<<",\tA="<<parte.getAgregadas()<<endl;
            salida<<"\t"<<parte.getNombre()<<":\tT="<<parte.getTotal()<<",\tI="<<parte.getItems()<<",\tB="<<parte.getBase()<<",\tD="<<parte.getBorradas()<<",\tM="<<parte.getModificadas()<<",\tA="<<parte.getAgregadas()<<endl;
        }
    }
    cout<<"--------------------------------------------"<<endl;
    salida<<"--------------------------------------------"<<endl;
    cout<<"PARTES NUEVAS:\n";
    salida<<"PARTES NUEVAS:\n";
    for(auto parte: partes) {
        if(parte.esNueva()){
            total+=parte.getTotal();
            cout<<"\t"<<parte.getNombre()<<":\tT="<<parte.getTotal()<<",\tI="<<parte.getItems()<<endl;
            salida<<"\t"<<parte.getNombre()<<":\tT="<<parte.getTotal()<<",\tI="<<parte.getItems()<<endl;
        }
    }
    cout<<"--------------------------------------------"<<endl;
    salida<<"--------------------------------------------"<<endl;
    cout<<"PARTES REUSADAS:\n";
    salida<<"PARTES REUSADAS:\n";
    for(auto parte: partes) {
        if(parte.esReusada()){
            total+=parte.getTotal();
            cout<<"\t"<<parte.getNombre()<<":\tT="<<parte.getTotal()<<",\tI="<<parte.getItems()<<",\tB="<<parte.getBase()<<endl;
            salida<<"\t"<<parte.getNombre()<<":\tT="<<parte.getTotal()<<",\tI="<<parte.getItems()<<",\tB="<<parte.getBase()<<endl;
        }
    }
    cout<<"--------------------------------------------"<<endl;
    salida<<"--------------------------------------------"<<endl;
    cout<<"Total de LDC="<<total<<endl;
    salida<<"Total de LDC="<<total<<endl;

}

//.i
int main()
{
    //.d=3
    vector<Parte> partes;
    Analizador analizador;
    string filename;

    do {
        cout<<"Ingrese nombre del archivo a procesar (Teclee enter para terminar y generar reporte):"<<endl;
        getline(cin,filename);
        if(filename != ""){
            Lector lector;
            
            bool analizable = lector.abrir(filename);
            if(analizable) {
                Parte parte = analizador.analizarParte(lector);
                
                int i = parte.in(partes);
                if(i != -1) {
                    partes[i] += parte;
                } else {
                    partes.push_back(parte);
                }
                cout<<"Archivo analizado correctamente. ";
            }
        }
    } while (filename != "");

    imprimir(partes);
    
    return 0;
}