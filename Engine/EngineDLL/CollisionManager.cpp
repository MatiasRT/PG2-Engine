#include "CollisionManager.h"

CollisionManager* CollisionManager::instance = NULL;

CollisionManager::CollisionManager() {
	for (int i = 0; i < (int)Layers::count; i++) {
		colliders.push_back(new list<Entity*>());
	}
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