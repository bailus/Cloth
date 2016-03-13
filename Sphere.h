/*
 * Sphere.h
 *
 *  Created on: 18/10/2014
 *      Author: sam
 */

#ifndef SPHERE_H_
#define SPHERE_H_

#include "Thing.h"

class Sphere: public Thing {
public:
	Sphere(glm::vec3 position, float radius, glm::vec4 color);
	virtual ~Sphere();

	void collision(std::vector<Particle> *particles);
	void display(Shader *shader);
	void move(glm::vec3 delta);

private:
	glm::vec4 color;
	float radius;
	glm::vec3 pos;
};

#endif /* SPHERE_H_ */
