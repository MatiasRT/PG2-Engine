#pragma once
#include <list>
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Entity.h"
#include "Exports.h"
using namespace std;

class ENGINEDLL_API CollisionManager {

	static CollisionManager* instance;

	vector<list<Entity*>*> colliders;
	//vector<list<Sprite*>*>* circles;

	/*void LayersMatchBox(list<Sprite*>* layerA, list<Sprite*>* layerB);
	void LayersMatchCircle(list<Sprite*>* layerA, list<Sprite*>* layerB);
	
	void CollisionBoxMath(Sprite* A, Sprite* B);
	void CollisionCircleMath(Sprite* A, Sprite* B);*/

public:
	CollisionManager();
	~CollisionManager();
	/*void FillingBoxList(Layers layer, Sprite* s);
	void FillingCircleList(Layers layer, Sprite* s);
	void CircleCollisionDetector();
	void BoxCollisionDetector();*/

	void AddCollisionEntity(Entity* e, Layers lyr);
	void CollisionDetector();
	void CheckCollisionsBetweenLayers(list<Entity*> *layerA, list<Entity*> *layerB);
	void CollisionBoxResolver(Entity* A, Entity* B);

	static CollisionManager* Instance() {
		if (instance == NULL) {
			instance = new CollisionManager();
		}
		return instance;
	};
};