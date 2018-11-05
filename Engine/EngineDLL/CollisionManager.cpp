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
	 
}

void CollisionManager::CollisionBoxMath() {

}

void CollisionManager::CollisionCircleMath() {

}

void CollisionManager::CircleCollisionDetecter() {

}

void CollisionManager::BoxCollisionDetecter() {
	/*for (int i = 0; i < (int)Layers::Count; i++) {
		
		
	}*/
}