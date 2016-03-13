/*
 * Particle.cpp
 *
 *  Created on: 15/10/2014
 *      Author: sam
 */

#include "Particle.h"

Particle::Particle(glm::vec3 pos, float mass, float damping, glm::vec2 texCoord) {
	this->pos = pos;
	this->lastPos = pos;
	this->mass = mass;
	this->damping = damping;
	this->texCoord = texCoord;

	force = glm::vec3(0,0,0);
	isStatic = false;
}

Particle::~Particle() {
	// TODO Auto-generated destructor stub
}

void Particle::move(glm::vec3 delta) {
	if (isStatic) return;
	pos += delta;
}

void Particle::step(float timeStep) {
	if (isStatic) return;

	//apply force
	glm::vec3 temp = pos;
	pos += (pos-lastPos) * damping + (force/mass)*(timeStep/100);
	lastPos = temp;
	force = glm::vec3(0,0,0);
}
