#include "Entidad.h"


Entidad::Entidad(string n, int v, int a){
nombre = n;
vida = v;
ataque = a;
fila = 0;
columna = 0;
simbolo = ' ';
}

string Entidad::getNombre(){
    return nombre;
}

int Entidad::getVida(){
    return vida;
}

int Entidad::getAtaque(){
	return ataque;
}


void Entidad::setX(int fila){
    this->fila = fila;
}

void Entidad::setY(int columna){
    this->columna = columna;
}

int Entidad::getX(){
    return fila;
}

int Entidad::getY(){
    return columna;
}

void Entidad::setSimbolo(char s){
    this->simbolo = s;
}

char Entidad::getSimbolo(){
    return simbolo;
}

void Entidad::recibirDanio(int dano)
{

    vida -= dano;


    if(vida < 0)
        vida = 0;


    cout << nombre
         << " recibe "
         << dano
         << " daño\n";

}

void Entidad::mostrarDatos(){

cout << "\033[34m";
cout << nombre << "\033[0m";
cout << "\033[32m";
cout << "	hp: " << vida << "\n" << endl;
cout << "\033[0m";
}
