#ifndef MAPA_H
#define MAPA_H

class Mapa {
	private:
	  int filas;
	  int columnas;
	  char mapa[10][20];

	public:
	  Mapa();
     void dibujar();
	void colocarElemento(int fila, int columna, char simbolo);
};
#endif
