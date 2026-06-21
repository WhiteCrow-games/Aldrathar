#include <string>
#include "Entidad.h"

Entidad::Entidad(string n, int a, int v, int d,int vl, float p, int e) {
	nombre = n;
	ataque = a;
	vida = v;
	defensa = d;
	velocidad = vl;
	peso = p;
	edad = e;
}
	int Entidad::getDefensa(){
	return defensa; }

	float Entidad::getPeso(){
	return peso;}

	string Entidad::getNombre() {
	return nombre;}

	int Entidad::getVida() {
	return vida;}

	int Entidad::getVelocidad(){
	return velocidad;}

	int Entidad::getAtaque() {
 	return ataque;}

	int Entidad::getEdad(){
   	return edad;}


	void Entidad::atacar(string nombre_) {
	    cout << "\n-" << nombre << " ataca a " << nombre_ << endl;
}

	void Entidad::mostrarDatosMenu() {
    cout << nombre << endl;
    cout << "vida: " << vida << endl;
    cout << "ataque: " << ataque << endl;
}

	void Entidad::mostrarDatos() {
    cout << "\n" << nombre
         << " " << vida << endl;
}

	void Entidad::name() {
    cout << nombre << endl;
}

	void Entidad::recibirDanio(int cantidad) {
    vida -= cantidad;

    cout << nombre << " ha recibido "
         << cantidad << " pts de daño\n";

    if (vida <= 0) {
        vida = 0;
        cout << "\nVictoria!!!\n";
    }
}
.
