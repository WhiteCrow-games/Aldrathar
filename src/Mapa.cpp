#include <iostream>
#include "Mapa.h"
using namespace std;
Mapa::Mapa(){
	filas = 10;
	columnas = 20;

	for (int i = 0; i < filas; i++){
	    for (int j = 0; j < columnas; j++){
	        mapa[i][j] = '.';
   		 }
	}
} //Mapa
void Mapa::dibujar()
{
	for (int i = 0; i < filas; i++){
        for (int j = 0; j < columnas; j++)
        {
            cout << mapa[i][j];
        }

        cout << endl;
    }

}
