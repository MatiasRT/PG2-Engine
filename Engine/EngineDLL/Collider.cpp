#include "Collider.h"

Collider::Collider(glm::vec2 pPosition, float h, float w, Layers l, bool stc) {
	pivotPosition = pPosition;
	height = h;
	width = w;
	layer = l;
	isStatic = stc;
}