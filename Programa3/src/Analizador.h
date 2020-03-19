#include <math.h>
#include <vector>
using namespace std;

class Analizador {
public:
  double sumarListaConPotencia(vector<double> lista, int power);
  double promedioLista(vector<double> lista);
  double sumarProductoListas(vector<double> listaA, vector<double> listaB);
};

//.i
double Analizador::sumarListaConPotencia(vector<double> lista, int power) {
  double sum = 0;

  for(auto item:lista) {
    sum += pow(item, power);
  }
  
  return sum;
}

//.i
double Analizador::promedioLista(vector<double> lista) {
  double sum = 0;

  for(auto item:lista) {
    sum += item;
  }

  return sum/lista.size();
}

//.i
double Analizador::sumarProductoListas(vector<double> listaA, vector<double> listaB) {
  double sum = 0;

  for(int i=0; i<listaA.size(); i++) {
    sum += listaA[i] * listaB[i];
  }
  
  return sum;
}