#include "Personaje.h"

Personaje::Personaje(string n, string ap, int e, int v, int a, int lvl) {
    nombre = n;
    apellido = ap;
    edad = e;
    vida = v;
    ataque = a;
    nivel = lvl;
}

	string Personaje::getNombre() {
	return nombre; }

	int Personaje::getVida() {
        return vida; }

	int Personaje::getAtaque() {
	return ataque;}

	int Personaje::getVelocidad(){
	return velocidad; }

	int Personaje::getEdad(){
	return edad;}

	float Personaje:: getPeso(){
	return peso; }

	int Personaje::getDefensa(){
	return defensa; }

	string Personaje::getApellido(){
	return apellido;}

	string Personaje::getCasa(){
	return casa;}

	int Personaje::getLvl() {
        return nivel; }

void Personaje::name() {
    cout << getNombre() << endl;
}

void Personaje::mostrarDatos() {
    cout << "\nNombre: " << getNombre() << endl;
    cout << "Vida: " << getVida() << endl;
    cout << "Lvl: " << getLvl() << endl;
}

void Personaje::atacar(string nombre_) {
    cout << "\n-" << nombre << " ataca a " << nombre_ << endl;
}

void Personaje::recibirDanio(int cantidad) {
    vida -= cantidad;

    cout << nombre << " ha recibido "
         << cantidad << " pts de daño\n";

    if (vida <= 0) {
        vida = 0;
        cout << nombre << " esta muerto!" << endl;
    }
}

     void Personaje::mostrarDatosMenu(
cout << "\nNombre: " << getNombre() << endl;
    cout << "Vida: " << getVida() << endl;
    cout << "Lvl: " << getLvl() << endl;
);
