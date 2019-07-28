#include "CollisionManager.h"

CollisionManager* CollisionManager::instance = NULL;

CollisionManager::CollisionManager() {
	/*circles = new vector<list<Sprite*>*>((int)Layers::Count);												// Creo un vector de punteros de listas de punteros de sprites con tamaño de la cantidad de layers que tenga (para eso uso Count en el enum de layers) 
	boxes = new vector<list<Sprite*>*>((int)Layers::Count);													// Creo un vector de punteros de listas de punteros de sprites con tamaño de la cantidad de layers que tenga
	for (int i = 0; i < Layers::Count; i++) {
		circles->at(i) = new list<Sprite*>();																// En cada posicion del vector circles creo una lista de sprites
		boxes->at(i) = new list<Sprite*>();																	// En cada posicion del vector boxes creo una lista de sprites
	}*/
	for (int i = 0; i < (int)Layers::count; i++) {
		colliders.push_back(new list<Entity*>());
	}
}

CollisionManager::~CollisionManager() {
	/*for (int i = 0; i < Layers::Count; i++) {
		delete circles->at(i);
		delete boxes->at(i);
	}
	delete circles;
	delete boxes;*/
}


void CollisionManager::AddCollisionEntity(Entity* e, Layers lyr) {
	colliders[lyr]->push_back(e);
}

void CollisionManager::CollisionDetector() {

	for (int i = 0; i < (int)Layers::count; i++) {
		for (int j = i + 1; j < (int)Layers::count; j++) {
			CheckCollisionsBetweenLayers(colliders[i], colliders[j]);
		}
	}
}

void CollisionManager::CheckCollisionsBetweenLayers(list<Entity*> *layerA, list<Entity*> *layerB) {

	for (list<Entity*>::iterator i = layerA->begin(); i != layerA->end(); ++i) {
		for (list<Entity*>::iterator j = layerB->begin(); j != layerB->end(); ++j) {
			CollisionBoxResolver(*i, *j);
		}
	}

}

void CollisionManager::CollisionBoxResolver(Entity* A, Entity* B) {

	glm::vec2 translateA = glm::vec2(A->GetTranslationX(), A->GetTranslationY());
	glm::vec2 translateB = glm::vec2(B->GetTranslationX(), B->GetTranslationY());
	glm::vec2 module = abs((translateA + A->GetColliderPivot()) - (translateB + B->GetColliderPivot()));

	if (module.x < (A->GetColliderWidth() + B->GetColliderWidth()) / 2.0f && module.y < (A->GetColliderHeight() + B->GetColliderHeight()) / 2.0f) {

		float penetrationX = ((A->GetColliderWidth() / 2.0f) + (B->GetColliderWidth() / 2.0f)) - module.x;
		float penetrationY = ((A->GetColliderHeight() / 2.0f) + (B->GetColliderHeight() / 2.0f)) - module.y;

		if (penetrationX > penetrationY) {
			if (A->GetColliderIsStatic()) {
				if (B->GetTranslationY() < A->GetTranslationY())
					B->SetTranslation(B->GetTranslationX(), B->GetTranslationY() - penetrationY, B->GetTranslationZ());
				else
					B->SetTranslation(B->GetTranslationX(), B->GetTranslationY() + penetrationY, B->GetTranslationZ());
			}
			else if (B->GetColliderIsStatic()) {
				if (A->GetTranslationY() < B->GetTranslationY())
					A->SetTranslation(A->GetTranslationX(), A->GetTranslationY() - penetrationY, A->GetTranslationZ());
				else
					A->SetTranslation(A->GetTranslationX(), A->GetTranslationY() + penetrationY, A->GetTranslationZ());
			}
			else {
				if (B->GetTranslationY() < A->GetTranslationY()) {
					A->SetTranslation(A->GetTranslationX(), A->GetTranslationY() + (penetrationY / 2), A->GetTranslationZ());
					B->SetTranslation(B->GetTranslationX(), B->GetTranslationY() - (penetrationY / 2), B->GetTranslationZ());
				}
				else {
					A->SetTranslation(A->GetTranslationX(), A->GetTranslationY() - (penetrationY / 2), A->GetTranslationZ());
					B->SetTranslation(B->GetTranslationX(), B->GetTranslationY() + (penetrationY / 2), B->GetTranslationZ());
				}
			}
		}
		else if (penetrationX < penetrationY) {
			if (A->GetColliderIsStatic()) {
				if (B->GetTranslationX() < A->GetTranslationX())
					B->SetTranslation(B->GetTranslationX() - penetrationX, B->GetTranslationY(), B->GetTranslationZ());
				else
					B->SetTranslation(B->GetTranslationX() + penetrationX, B->GetTranslationY(), B->GetTranslationZ());
			}
			else if (B->GetColliderIsStatic()) {
				if (A->GetTranslationX() < B->GetTranslationX())
					A->SetTranslation(A->GetTranslationX() - penetrationX, A->GetTranslationY(), A->GetTranslationZ());
				else
					A->SetTranslation(A->GetTranslationX() + penetrationX, A->GetTranslationY(), A->GetTranslationZ());
			}
			else {
				if (B->GetTranslationX() < A->GetTranslationX()) {
					A->SetTranslation(A->GetTranslationX() + (penetrationX / 2), A->GetTranslationY(), A->GetTranslationZ());
					B->SetTranslation(B->GetTranslationX() - (penetrationX / 2), B->GetTranslationY(), B->GetTranslationZ());
				}
				else {
					A->SetTranslation(A->GetTranslationX() - (penetrationX / 2), A->GetTranslationY(), A->GetTranslationZ());
					B->SetTranslation(B->GetTranslationX() + (penetrationX / 2), B->GetTranslationY(), B->GetTranslationZ());
				}
			}
		}
	}
}







//void CollisionManager::FillingBoxList(Layers layer, Sprite* s) {
	//boxes->at(layer)->push_back(s);																			// En la posicion especifica del vector(determinado por el layer que le mando) le guardo el sprite que quiero
//}	

//void CollisionManager::FillingCircleList(Layers layer, Sprite* s) {
	//circles->at(layer)->push_back(s);																		// En la posicion especifica del vector(determinado por el layer que le mando) le guardo el sprite que quiero
//}

//void CollisionManager::BoxCollisionDetector() {
	/*for (int i = 0; i < (int)Layers::Count; i++) {															// Con estos dos fors recorremos los layers para asignar los matches
		for (int j = 0; j < (int)Layers::Count; j++) {
			if (j == i) continue;																			// Si es la misma layer se lo tiene que saltar
			
			if (j == Layers::Tiles_layer || i == Layers::Tiles_layer) {
				//cout << "i: " << i << " j:" << j << endl;
				continue;
			}
				LayersMatchBox(boxes->at(i), boxes->at(j));
		}
	}*/
//}

//void CollisionManager::CircleCollisionDetector() {
	/*for (int i = 0; i < (int)Layers::Count; i++) {															// Con estos dos fors recorremos los layers para asignar los matches
		for (int j = 0; j < (int)Layers::Count; j++) {
			if (j == i) continue;																			// Si es la misma layer se lo tiene que saltar
			if (j == Layers::Tiles_layer || i == Layers::Tiles_layer) continue;
				LayersMatchCircle(circles->at(i), circles->at(j));
		}
	}*/
//}

//void CollisionManager::LayersMatchBox(list<Sprite*>* layerA, list<Sprite*>* layerB) {						// Ven las colisiones entre los layers (cajas)
	/*for (list<Sprite*>::iterator i = layerA->begin(); i != layerA->end(); ++i){
		for (list<Sprite*>::iterator j = layerB->begin(); j != layerB->end(); ++j) {
			CollisionBoxMath(*i, *j);																		// Le mandamos por parametro los sprites a la funcion que resuelve la colision
		}
	}*/
//}

//void CollisionManager::LayersMatchCircle(list<Sprite*>* layerA, list<Sprite*>* layerB) {					// Ven las colisiones entre los layers (circulos)
	/*for (list<Sprite*>::iterator i = layerA->begin(); i != layerA->end(); ++i) {
		for (list<Sprite*>::iterator j = layerB->begin(); j != layerB->end(); ++j) {
			CollisionCircleMath(*i, *j);																	// Le mandamos por parametro los sprites a la funcion que resuelve la colision
		}
	}*/
//}

//void CollisionManager::CollisionBoxMath(Sprite* A, Sprite* B) {
	/*BoundingBox* boxA = A->GetBoundingBox();																// Obtenemos la caja de colision del sprite n1
	BoundingBox* boxB = B->GetBoundingBox();																// Obtenemos la caja de colision del sprite n2

	glm::vec2 diff = boxA->GetPos() - boxB->GetPos();														// Obtenemos la diferencia

	float moduleX = abs(diff.x);																			// Modulo de X
	float moduleY = abs(diff.y);																			// Modulo de Y
	
	float masses = boxA->GetMass() + boxB->GetMass();														// Obtengo el total de las masas de los dos objetos
	float aMass = (boxA->GetMass() / masses) * 10;															// El porcentaje de masa del primer objeto
	float bMass = (boxB->GetMass() / masses) * 10;															// El porcentaje de masa del segundo objeto
 
	if (!boxA->IsStatic() || !boxB->IsStatic()) {															// Si las dos son estaticas que no haga los calculos

		if (!boxA->IsTrigger() || !boxB->IsTrigger()) {														// Si las dos son triggers que no hagan los calculos

			if (moduleX <= (boxA->GetWidth() / 2 + boxB->GetWidth() / 2) && moduleY <= (boxA->GetHeight() / 2 + boxB->GetHeight() / 2)) {

				float inX = (boxA->GetWidth() / 2 + boxB->GetWidth() / 2) - moduleX;						// Cuanto penetra en X	(¿Tiene que ser valor absoluto?)
				float inY = (boxA->GetHeight() / 2 + boxB->GetHeight() / 2) - moduleY;						// Cuanto penetra en Y

				if (inX > inY) {																			// Si se penetra mas verticalmente
					if (boxA->IsStatic()) {
						if (!boxB->IsTrigger()) {
							B->SetPos(boxB->GetX(), boxB->GetY() - inY, 0);									// Si la caja A es estatica, que la caja B salga para afuera la cantidad de penetracion que hubo en Y
							boxB->SetCollision(true);														// Avisamos al Bounding Box que hubo colision.	
						}
					}
					else {
						if (boxB->IsStatic()) {
							if (!boxA->IsTrigger()) {
								A->SetPos(boxA->GetX(), boxA->GetY() - inY, 0);								// Si la caja B es estatica, que la caja A salga para afuera la cantidad de penetracion que hubo en Y
								boxA->SetCollision(true);													// Avisamos al Bounding Box que hubo colision.	
							}
						}
						else {
							if(!boxA->IsTrigger())
								if (!boxB->IsTrigger()) {
									A->SetPos(boxA->GetX(), boxA->GetY() - (inY / aMass), 0);				// Se deberia mover segun la masa que tenga.
									B->SetPos(boxB->GetX(), boxB->GetY() + (inY / bMass), 0);
								}
						}
					}
				}
				else {																						// Si se penetra mas horizontalmente
					if (boxA->IsStatic()) {
						if (!boxB->IsTrigger()) {
							B->SetPos(boxB->GetX() - inX, boxB->GetY(), 0);									// Si la caja A es estatica, que la caja B salga para afuera la cantidad de penetracion que hubo en X
							boxB->SetCollision(true);														// Avisamos al Bounding Box que hubo colision.	
						}
					} 
					else {
						if (boxB->IsStatic()) {
							if (!boxA->IsTrigger()) {
								A->SetPos(boxA->GetX() - inX, boxA->GetY(), 0);								// Si la caja B es estatica, que la caja A salga para afuera la cantidad de penetracion que hubo en X
								boxA->SetCollision(true);													// Avisamos al Bounding Box que hubo colision.	
							}
						}
						else {
							if (!boxA->IsTrigger())
								if (!boxB->IsTrigger()) {
									A->SetPos(boxA->GetX() - (inX / aMass), boxA->GetY(), 0);				// Se deberian mover a la mitad de la distancia
									B->SetPos(boxB->GetX() + (inX / bMass), boxB->GetY(), 0);
								}
						}
					}
				}
			}
		}
	}*/
//}

//void CollisionManager::CollisionCircleMath(Sprite* A, Sprite* B) {
	/*BoundingCircle* circleA = A->GetBoundingCircle();
	BoundingCircle* circleB = B->GetBoundingCircle();

	glm::vec2 diff = circleA->GetPos() - circleB->GetPos();

	float moduleX = abs(diff.x);
	float moduleY = abs(diff.y);
	float dist = ((moduleX * 2) + (moduleY * 2));															// Distancia al cuadrado

	if (dist*2 < ((circleA->GetRadius() + circleB->GetRadius()) * 2)) {										// Si esto ocurre, hay colision
		float dist = ((circleA->GetRadius() + circleB->GetRadius()) * 2);
		float insideCircle = ((circleA->GetRadius() + circleB->GetRadius()) - dist);						// Penetracion en el circulo
		glm::vec2 dirA = glm::normalize(A->GetPos());														// Direccion en X a la que va a ser expulsado
		glm::vec2 dirB = glm::normalize(B->GetPos());														// Direeccion en Y a la que va a ser expulsado
		//unsigned int dirX = diff.x / moduleX;																	
		//unsigned int dirY = diff.y / moduleY;	

		// Para expulsar deberia tener las direcciones de los dos objetos que colisionaron (dirA y dirB), y ver cual es la fuerza que se le aplica para retornarla y que salga con esa cantidad de fuerza.
	}*/
//}