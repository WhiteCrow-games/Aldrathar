#include "Entidad.h"


Entidad::Entidad(string n, int v, int a, int x, int y, char s){
nombre = n;
vida = v;
ataque = a;
fila = x;
columna = y;
simbolo = s;
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

void Entidad::setX(int x);

void  Entidad::setY(int y);

int Entidad::getX(){
	return x;
}

int Entidad::getY(){
	return y;
}

int Entidad::getVida(){
    return vida;
 }
void  Entidad::setSimbolo(char s);

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
