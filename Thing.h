/*
 * Thing.h
 *
 *  Created on: 18/10/2014
 *      Author: sam
 */

#ifndef THING_H_
#define THING_H_

#include "Includes.h"
#include "Particle.h"
#include "Shader.h"

class Thing {
public:
	virtual void collision(std::vector<Particle> *particles) = 0;
	virtual void display(Shader *shader) = 0;
	virtual void move(glm::vec3 delta) = 0;
};

#endif /* THING_H_ */
