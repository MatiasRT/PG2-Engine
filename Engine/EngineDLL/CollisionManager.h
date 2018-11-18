#pragma once
#include <list>
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Entity.h"
#include "Sprite.h"
#include "BoundingBox.h"
#include "BoundingCircle.h"
#include "Exports.h"
using namespace std;

class ENGINEDLL_API CollisionManager {

	vector<list<Sprite*>*>* boxes;
	vector<list<Sprite*>*>* circles;

	void LayersMatchBox(list<Sprite*>* layerA, list<Sprite*>* layerB);
	void LayersMatchCircle(list<Sprite*>* layerA, list<Sprite*>* layerB);
	
	void CollisionBoxMath(Sprite * A, Sprite * B);
	void CollisionCircleMath(Sprite * A, Sprite * B);
public:
	CollisionManager();
	~CollisionManager();
	void FillingBoxList(Layers layer, Sprite * s);
	void FillingCircleList(Layers layer, Sprite * s);
	void CircleCollisionDetector();
	void BoxCollisionDetector();
};