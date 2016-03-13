/*
 * Particle.h
 *
 *  Created on: 15/10/2014
 *      Author: sam
 */

#ifndef PARTICLE_H_
#define PARTICLE_H_

#include "Includes.h"

class Particle {
public:
	Particle(glm::vec3 pos, float mass, float damping, glm::vec2 texCoord);
	virtual ~Particle();

	bool isStatic;
	glm::vec3 normal;
	glm::vec3 pos;
	glm::vec3 lastPos;
	glm::vec2 texCoord;
	float damping;
	float mass;
	glm::vec3 force;

	void move(glm::vec3 delta);
	void step(float timeStep);

};

#endif /* PARTICLE_H_ */
