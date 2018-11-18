#include "CollisionManager.h"

CollisionManager::CollisionManager() {
	circles = new vector<list<Sprite*>*>((int)Layers::Count);
	boxes = new vector<list<Sprite*>*>((int)Layers::Count);
	for (int i = 0; i < Layers::Count; i++) {
		circles->at(i) = new list<Sprite*>();
		boxes->at(i) = new list<Sprite*>();
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

void CollisionManager::FillingBoxList(Layers layer, Sprite * s) {
	boxes->at(layer)->push_back(s);
}

void CollisionManager::FillingCircleList(Layers layer, Sprite * s) {
	circles->at(layer)->push_back(s);
}


void CollisionManager::BoxCollisionDetector() {
	for (int i = 0; i < (int)Layers::Count; i++) {															//Con estos dos fors recorremos las layers para asignar los matches
		for (int j = 0; j < (int)Layers::Count; j++) {
			if (j == i) continue;																			// Si es la misma layer se lo tiene que saltar
			LayersMatchBox(boxes->at(i), boxes->at(j));
		}
	}
}

void CollisionManager::CircleCollisionDetector() {
	for (int i = 0; i < (int)Layers::Count; i++) {															// Con estos dos fors recorremos las layers para asignar los matches
		for (int j = 0; j < (int)Layers::Count; j++) {
			if (j == i) continue;																			// Si es la misma layer se lo tiene que saltar
			LayersMatchCircle(circles->at(i), circles->at(j));
		}
	}
}

void CollisionManager::LayersMatchBox(list<Sprite*>* layerA, list<Sprite*>* layerB) {				// Ven las colisiones entre los layers (cajas)
	for (list<Sprite*>::iterator i = layerA->begin(); i != layerA->end(); ++i){
		for (list<Sprite*>::iterator j = layerB->begin(); j != layerB->end(); ++j) {
			CollisionBoxMath(*i, *j);
		}
	}
}

void CollisionManager::LayersMatchCircle(list<Sprite*>* layerA, list<Sprite*>* layerB) {		// Ven las colisiones entre los layers (circulos)
	for (list<Sprite*>::iterator i = layerA->begin(); i != layerA->end(); ++i) {
		for (list<Sprite*>::iterator j = layerB->begin(); j != layerB->end(); ++j) {
			CollisionCircleMath(*i, *j);
		}
	}
}

void CollisionManager::CollisionBoxMath(Sprite * A, Sprite * B) {
	//BoundingBox* boxA = A->GetBoundingBox();																// Obtenemos la caja de colision del sprite n1
	//BoundingBox* boxB = B->GetBoundingBox();																// Obtenemos la caja de colision del sprite n1
	glm::vec2 diff = boxA->GetPos() - boxB->GetPos();																// Obtenemos la diferencia
	float moduleX = abs(diff.x);																		// Modulo de X
	float moduleY = abs(diff.y);																		// Modulo de Y

	/* FALTA SI ES TRIGGER */
	if (moduleX <= (boxA.GetWidth()/2 + B.GetWidth()/2) && moduleY <= (boxA.GetHeight()/2 + B.GetHeight()/2)) {
		float inX = (boxA.GetWidth() / 2 + B.GetWidth() / 2) - moduleX;									// Cuanto penetra en X	(¿Tiene que ser valor absoluto?)
		float inY = (boxA.GetHeight() / 2 + B.GetHeight() / 2) - moduleY;								// Cuanto penetra en Y
		if (inX > inY) {																					// Si se penetra mas verticalmente
			if (boxA.isStatic())
				B.SetPos(B.GetX(), B.GetY() - inY);
			else if(B.isStatic())
				A.SetPos(A.GetX(), A.GetY() - inY);
			else {
				A.SetPos(A.GetX(), A.GetY() - (inY/2));														// Se deberian mover a la mitad de la distancia
				B.SetPos(B.GetX(), B.GetY() - (inY/2));
			}
		}
		else {																								// Si se penetra mas horizontalmente
			if (A.isStatic())
				B.SetPos(B.GetX(), B.GetY() - inX);
			else if (B.isStatic())
				A.SetPos(A.GetX(), A.GetY() - inX);
			else {
				A.SetPos(A.GetX(), A.GetY() - (inX / 2));													// Se deberian mover a la mitad de la distancia
				B.SetPos(B.GetX(), B.GetY() - (inX / 2));
			}
		}
	}
}

void CollisionManager::CollisionCircleMath(Sprite * A, Sprite * B) {
	/*glm::vec2 diff = A.GetPos() - B.GetPos();
	unsigned int moduleX = abs(diff.x);
	unsigned int moduleY = abs(diff.y);
	unsigned int dist = ((moduleX * 2) + (moduleY * 2));													// Distancia al cuadrado

	if (dist*2 < ((A.GetRadius() + B.GetRadius()) * 2)) {													// Si esto ocurre, hay colision
		unsigned int dist = ((A.GetRadius() + B.GetRadius()) * 2);
		unsigned int insideCircle = ((A.GetRadius() + B.GetRadius()) - dist);								// Penetracion en el circulo
		glm::vec2 dirA = glm::normalize(A.GetPos());														// Direccion en X a la que va a ser expulsado
		glm::vec2 dirB = glm::normalize(B.GetPos());														// Direeccion en Y a la que va a ser expulsado
		//unsigned int dirX = diff.x / moduleX;																	
		//unsigned int dirY = diff.y / moduleY;	

		// Para expulsar deberia tener las direcciones de los dos objetos que colisionaron (dirA y dirB), y ver cual es la fuerza que se le aplica para retornarla y que salga con esa cantidad de fuerza.
	
		
	}
	*/
}