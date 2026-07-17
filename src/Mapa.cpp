#include <iostream>
#include "Mapa.h"
using namespace std;

/**
*Matris de mapa
*/
	Mapa::Mapa(){
	filas = 20;
	columnas = 40;

	for (int i = 0; i < filas; i++){
	    for (int j = 0; j < columnas; j++){
	        mapa[i][j] = '.';
   		 }
	}
} //Mapa()

	void Mapa::dibujar(){
	for (int i = 0; i < filas; i++){
	        for (int j = 0; j < columnas; j++){
            cout << mapa[i][j];
        		}//for
        cout << endl;
	}//for
} //dibujar()
	void Mapa::colocarElemento(int fila, int columna, char simbolo){
		mapa[fila][columna] = simbolo;
} //colocarElemento()
	void Mapa::pared(char simbolo){
		for(int i = 0;i < filas; i++){
		mapa[i][0] = simbolo;
		mapa[i][39] = simbolo;

		for(int i = 0;i < columnas; i++){
		mapa[0][i] = simbolo;
		mapa[19][i] = simbolo;
		}
}
} //pared()
