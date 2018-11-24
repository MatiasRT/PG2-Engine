#include "Spritesheet.h"

Spritesheet::Spritesheet(int tW, int tH, int col, int rows) {
	uvList = new list<float*>();															// Creo una lista de punteros de floats, donde se van a guardar los uv´s de la textura

	int countFrames = rows * col;															// Multiplico la cantidad de columnas y de filas que tiene el sprite para poder dibujar el correcto
	float wFrame = 1.0f / col;																// ancho de cada sprite dentro de la imagen.
	float hFrame = 1.0f / rows;																// alto de cada sprite dentro de la imagen.
	float x;
	float y;

	for (int i = 0; i < countFrames; i++) {													
		x = (i % countFrames) * wFrame;
		y = (i / countFrames) * hFrame;
		uvPositions = new float[8]{															// Llenamos el arreglo de uvs
			x / tW, 1 - ((y + hFrame) / tH),												// Este seria el punto arriba a la izquierda
			x / tW, 1 - y / tH,																// Este arriba a la derecha
			(x + wFrame) / tW , 1 - ((y + hFrame) / tH),									// Este abajo a la izquierda
			(x + wFrame) / tW, 1 - y / tH													// Y este abajo a la derecha
		};
		uvList->push_back(uvPositions);														// Le pasamos a la lista de uv los puntos guardados en el arreglo
	}
}

float * Spritesheet::GetSpritesheet(int frame) {
	int fr = 0;
	for (list<float*>::iterator i = uvList->begin; i != uvList->end(); i++)
		if (fr == frame)
			return *i;
		else fr++;
}