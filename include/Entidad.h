#ifndef ENTIDAD_H
#define ENTIDAD_H

#include <iostream>
#include <string>

using namespace std;


class Entidad
{

protected:

    string nombre;

    int vida;
int ataque;
int fila;
int columna;
char simbolo;

public:

    Entidad(string n, int v, int a, int x, int y, char s);


    string getNombre();

    int getVida();
int getAtaque();
void setX(int x);
void setY(int y);
void setSimbolo(char s);
char getSimbolo();
int getX();
int getY();

    void recibirDanio(int dano);		// v0.0.1
	void mostrarDatos();			// v
};


#endif
