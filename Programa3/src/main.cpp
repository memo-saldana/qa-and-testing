// Jose Guillermo Saldaña Cárdenas
// A01039888
// Programa que calcula la regresion lineal dada una lista de puntos, y calcula un nuevo valor a partir de una x dada.
#include <iostream>
#include <vector>
#include <iomanip>
#include "Lector.h"
#include "Analizador.h"

using namespace std;

//.b=64

//.i
vector<vector<double>> leerDatos(Lector &lector) {
    vector<vector<double>> res(2, vector<double> (0,0));
    double x,y;
    while(!lector.fin()) {
        string linea = lector.getSigLinea();
        
        int comma = linea.find(",");

        if(comma == -1) {
            throw runtime_error("Error: Uno de los renglones no tiene par de valores, favor de verificar.");
        }

        string xString = linea.substr(0, comma);
        string yString = linea.substr(comma+1);
        try {
            x = stod(xString);
            y = stod(yString);
            
        }
        catch(const std::exception& e) {
            throw runtime_error("Error: Uno de los valores no es valido.");
        }
        

        if(y < 0 || x < 0){
            throw runtime_error("Error: Los valores no pueden ser negativos.");
        }

        res[0].push_back(x);
        res[1].push_back(y);
    }

    if(res[0].size() == 0){
        throw runtime_error("Error: Se deben tener valores para hacer los calculos");
    }

    return res;
}

//.i
double calcB1(vector<vector<double>> valores) {
    Analizador analizador;
    
    double avgX = analizador.promedioLista(valores[0]);
    double avgY = analizador.promedioLista(valores[1]);
    double N = valores[0].size();
    double B1 = (analizador.sumarProductoListas(valores[0], valores[1]) - 
                    (N * avgX * avgY)) /
                (analizador.sumarListaConPotencia(valores[0], 2) - 
                    (N * pow(avgX, 2)));

    return B1;
}

//.i
double calcB0(vector<vector<double>> valores, double B1) {
    Analizador analizador;
    
    double avgX = analizador.promedioLista(valores[0]);
    double avgY = analizador.promedioLista(valores[1]);
    
    return avgY - (B1 * avgX);
}

//.i
double calcR(vector<vector<double>> valores) {
    Analizador analizador;

    double sumX = analizador.sumarListaConPotencia(valores[0], 1);
    double sumY = analizador.sumarListaConPotencia(valores[1], 1);
    double n = valores[0].size();
    double r = (n * analizador.sumarProductoListas(valores[0], valores[1]) - sumX * sumY) /
                sqrt((n*analizador.sumarListaConPotencia(valores[0], 2) -
                    pow(analizador.sumarListaConPotencia(valores[0], 1), 2)) *
                    (n*analizador.sumarListaConPotencia(valores[1], 2) -
                    pow(analizador.sumarListaConPotencia(valores[1], 1), 2)));

    return r;
}

//.i
double calcR2(double r) {
    return r * r;
}

//.i
double calcYK(double B0, double B1, double xK) {
    return B0 + B1 * xK;
}

//.i
void imprimir(int n, double xK, double r, double r2, double B0, double B1, double yK) { //.m
    //.d=35
    cout<<"N  = "<<n<<endl;
    cout<<"xk = "<<xK<<endl;
    cout<<fixed<<setprecision(5);
    cout<<"r  = "<<r<<endl;
    cout<<"r2 = "<<r2<<endl;
    cout<<"b0 = "<<B0<<endl;
    cout<<"b1 = "<<B1<<endl;
    cout<<"yk = "<<yK<<endl;
}

//.i
int main() {

    vector<vector<double>> valores; //.m
    Lector lector; //.m
    string temp; //.m

    double xK, yK, B1, B0, r, r2;
    //.d=13
    cout<<"Teclee el archivo, con terminacion:\n";
    getline(cin, temp);
    while(temp == "") {
        cout<<"El nombre no puede estar vacio, vuelvelo a teclear, con terminacion:\n";
        getline(cin, temp);
    }

    lector.abrir(temp);

    temp = lector.getSigLinea();

    try {
        xK = stod(temp);
    }
    catch(const std::exception& e) {
        throw runtime_error("Error: El valor de xk no es valido.");
    }
    
    if(xK < 0) {
        throw runtime_error("Error: xK no puede ser negativo.");
    }


    valores = leerDatos(lector);


    B1 = calcB1(valores);
    B0 = calcB0(valores, B1);
    r = calcR(valores);
    r2 = calcR2(r);
    yK = calcYK(B0, B1, xK);

    imprimir(valores[0].size(), xK, r, r2, B0, B1, yK); //.m
    return 0;
}