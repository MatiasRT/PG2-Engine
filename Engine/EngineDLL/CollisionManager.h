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

	void CollisionBoxMath();
	void CollisionCircleMath();
public:
	CollisionManager();
	~CollisionManager();
	void CircleCollisionDetecter();
	void BoxCollisionDetecter();
};