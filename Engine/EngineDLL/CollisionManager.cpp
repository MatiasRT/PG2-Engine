#include "CollisionManager.h"

CollisionManager::CollisionManager() {
	circles = new vector<list<BoundingCircle>*>((int)Layers::Count);
	boxes = new vector<list<BoundingBox>*>((int)Layers::Count);
	for (int i = 0; i < Layers::Count; i++) {
		circles->at(i) = new list<BoundingCircle>();
		boxes->at(i) = new list<BoundingBox>();
	}
}

CollisionManager::~CollisionManager() {
	for (int i = 0; i < Layers::Count; i++) {
		delete circles->at(i);
		delete boxes->at(i);
	}
	delete circles;
	delete boxes;
}

void CollisionManager::BoxCollisionDetecter() {
	for (int i = 0; i < (int)Layers::Count; i++) {															//Con estos dos fors recorremos las layers para asignar los matches
		for (int j = 0; j < (int)Layers::Count; j++) {
			if (j == i) continue;																			// Si es la misma layer se lo tiene que saltar
			LayersMatchBox(boxes->at(i), boxes->at(j));
		}
	}
}

void CollisionManager::CircleCollisionDetecter() {
	for (int i = 0; i < (int)Layers::Count; i++) {															// Con estos dos fors recorremos las layers para asignar los matches
		for (int j = 0; j < (int)Layers::Count; j++) {
			if (j == i) continue;																			// Si es la misma layer se lo tiene que saltar
			LayersMatchCircle(circles->at(i), circles->at(j));
		}
	}
}

void CollisionManager::LayersMatchBox(list<BoundingBox>* layerA, list<BoundingBox>* layerB) {				// Ven las colisiones entre los layers (cajas)
	for (list<BoundingBox>::iterator i = layerA->begin(); i != layerA->end(); ++i){						
		for (list<BoundingBox>::iterator j = layerB->begin(); j != layerB->end(); ++j) {
			CollisionBoxMath(*i, *j);
		}
	}
}

void CollisionManager::LayersMatchCircle(list<BoundingCircle>* layerA, list<BoundingCircle>* layerB) {		// Ven las colisiones entre los layers (circulos)
	for (list<BoundingCircle>::iterator i = layerA->begin(); i != layerA->end(); ++i) {
		for (list<BoundingCircle>::iterator j = layerB->begin(); j != layerB->end(); ++j) {
			CollisionCircleMath(*i, *j);
		}
	}
}

void CollisionManager::CollisionBoxMath(BoundingBox A, BoundingBox B) {
	glm::vec2 diff = A.GetPos() - B.GetPos();																// Obtenemos la diferencia
	unsigned int moduleX = abs(diff.x);																		// Modulo de X
	unsigned int moduleY = abs(diff.y);																		// Modulo de Y

	if (moduleX < (A.GetWidth()/2 + B.GetWidth()/2) && moduleY < (A.GetHeight()/2 + B.GetHeight()/2)) {
		unsigned int inX = (A.GetWidth() / 2 + B.GetWidth() / 2) - moduleX;									// Cuanto penetra X
		unsigned int inY = (A.GetHeight() / 2 + B.GetHeight() / 2) - moduleY;
		if (inX > inY) {																					// 
			if (A.isStatic()) 
				B.SetPos(B.GetX(), B.GetY() - inY);
			else if(B.isStatic())
				A.SetPos(A.GetX(), A.GetY() - inY);
			else {
				A.SetPos(A.GetX(), A.GetY() - (inY/2));														// Se deberian mover a la mitad de la distancia
				B.SetPos(B.GetX(), B.GetY() - (inY/2));
			}
		}
		else {
			if (A.isStatic())
				B.SetPos(B.GetX(), B.GetY() - inX);
			else if (B.isStatic())
				A.SetPos(A.GetX(), A.GetY() - inX);
			else {
				A.SetPos(A.GetX(), A.GetY() - (inX / 2));														// Se deberian mover a la mitad de la distancia
				B.SetPos(B.GetX(), B.GetY() - (inX / 2));
			}
		}
	}
}

void CollisionManager::CollisionCircleMath(BoundingCircle A, BoundingCircle B) {
	glm::vec2 diff = A.GetPos() - B.GetPos();
	unsigned int moduleX = abs(diff.x);
	unsigned int moduleY = abs(diff.y);
	unsigned int dist = ((moduleX * 2) + (moduleY * 2));														// Distancia al cuadrado

	if (dist < ((A.GetRadius() + B.GetRadius()) * 2)) {
		unsigned int dist = ((A.GetRadius() + B.GetRadius()) * 2);
		unsigned int insideCircle = ((A.GetRadius() + B.GetRadius()) - dist);										// Penetracion en el circulo
		glm::vec2 dirA = glm::normalize(A.GetPos());															// Direccion en X a la que va a ser expulsado
		glm::vec2 dirB = glm::normalize(B.GetPos());															// Direeccion en Y a la que va a ser expulsado
		//unsigned int dirX = diff.x / moduleX;																	
		//unsigned int dirY = diff.y / moduleY;	

		// Para expulsar deberia tener las direcciones de los dos objetos que colisionaron (dirA y dirB), y ver cual es la fuerza que se le aplica para retornarla y que salga con esa cantidad de fuerza
	}
}