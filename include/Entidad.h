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

    Entidad(string n, int v, int a);


    string getNombre();

    int getVida();
int getAtaque();
void setX(int fila);
void setY(int columna);
void setSimbolo(char sim);
char getSimbolo();
int getX();
int getY();

    void recibirDanio(int dano);	
	void mostrarDatos();
};


#endif
