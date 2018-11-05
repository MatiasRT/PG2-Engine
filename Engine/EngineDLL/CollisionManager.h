#pragma once
#include <list>
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Entity.h"
#include "BoundingBox.h"
#include "BoundingCircle.h"
#include "Exports.h"
using namespace std;

class ENGINEDLL_API CollisionManager {

	vector <list <BoundingCircle>*>* circles;
	vector <list <BoundingBox>*>* boxes;

	void LayersMatchBox(list<BoundingBox>* layerA, list<BoundingBox>* layerB);
	void LayersMatchCircle(list<BoundingCircle>* layerA, list<BoundingCircle>* layerB);
	void CollisionBoxMath(BoundingBox A, BoundingBox B);
	void CollisionCircleMath(BoundingCircle A, BoundingCircle B);
public:
	CollisionManager();
	~CollisionManager();
	void CircleCollisionDetecter();
	void BoxCollisionDetecter();
};