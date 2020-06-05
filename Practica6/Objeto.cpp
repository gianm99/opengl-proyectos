#include "Objeto.h"

Objeto::Objeto(glm::vec3 pos, glm::vec3 inc)
{
	this->pos = pos;
	this->inc = inc;
}

Objeto::Objeto() {}

void Objeto::setPos(glm::vec3 posicion) {
	this->pos = pos;
}

void Objeto::setInc(glm::vec3 incremento) {
	this->inc = incremento;
}

glm::vec3 Objeto::getPos() {
	return pos;
}

glm::vec3 Objeto::setInc() {
	return inc;
}
