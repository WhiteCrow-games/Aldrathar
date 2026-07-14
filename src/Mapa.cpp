#include <iostream>
#include "Mapa.h"
using namespace std;
/**
*Matris de mapa
*/
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

} //dibujar

	void Mapa::colocarElemento(int fila, int columna, char simbolo){
	    mapa[fila][columna] = simbolo;
} //colocarElemento

