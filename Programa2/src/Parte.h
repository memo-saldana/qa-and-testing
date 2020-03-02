#pragma once
#include <string>
#include <vector>
using namespace std;

class Parte
{
	private:
		int total, items, base, borradas, modificadas;
		string nombre;
    
	public:
		Parte(string nombre, int total, int items, int base, int borradas, int modificadas);
		string getNombre();
		int getTotal();
		int getItems();
		int getBase();
		int getBorradas();
		int getModificadas();        
		int getAgregadas();
		bool esBase();
		bool esNueva();
		bool esReusada();
		bool noEsValida();
		Parte& operator+=(const Parte& p);
		int in(vector<Parte> partes);
};

//.i
Parte::Parte(string nombre, int total, int items, int base, int borradas, int modificadas)
{
	this->nombre = nombre;
	this->total = total;
	this->items = items;
	this->base = base;
	this->borradas = borradas;
	this->modificadas = modificadas;
}

//.i
string Parte::getNombre() {
    return nombre;
}

//.i
int Parte::getTotal() {
    return total;
}

//.i
int Parte::getItems() {
    return items;
}

//.i
int Parte::getBase() {
    return base;
}

//.i
int Parte::getBorradas() {
    return borradas;
}

//.i
int Parte::getModificadas() {
    return modificadas;
}

//.i
int Parte::getAgregadas()
{
	return total - base + borradas;
}

//.i
bool Parte::esBase()
{
	return base > 0 && (modificadas > 0 || borradas > 0 || getAgregadas() > 0);
}

//.i
bool Parte::esNueva()
{
	return base == 0 && modificadas == 0 && getAgregadas() > 0; 
}

//.i
bool Parte::esReusada()
{
	return base > 0 && modificadas == 0 && getAgregadas() == 0;
}

//.i
bool Parte::noEsValida()
{
	return !esBase() && !esNueva() && !esReusada();
}

//.i
int Parte::in(vector<Parte> partes)
{
	for(int i = 0; i < partes.size(); i++){
		if(this->nombre == partes[i].nombre){
			return i;
		}
	}
	return -1;
}

//.i
Parte& Parte::operator+=(const Parte& p)
{
	this->total += p.total;
	this->items += p.items;
	this->base += p.base;
	this->borradas += p.borradas;
	this->modificadas += p.modificadas;

	return *this;
}

