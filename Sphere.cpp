/*
 * Sphere.cpp
 *
 *  Created on: 18/10/2014
 *      Author: sam
 */

#include "Sphere.h"

Sphere::Sphere(glm::vec3 position, float radius, glm::vec4 color) {
	this->pos = position;
	this->radius = radius;
	this->color = color;
}

Sphere::~Sphere() {
	// TODO Auto-generated destructor stub
}

void Sphere::collision(std::vector<Particle> *particles) {
	for (std::vector<Particle>::size_type i = 0; i < particles->size(); i++) {
		glm::vec3 v = (*particles)[i].pos - pos;
		float distance = glm::length(v);
		if (distance < radius)
			(*particles)[i].pos += glm::normalize(v)*(radius-distance);
	}
}

void Sphere::display(Shader *shader) {
	shader->setModelMatrix(glm::translate(pos));
	glColor3fv(glm::value_ptr(color));
	glutSolidSphere(radius, 30, 30);
}

void Sphere::move(glm::vec3 delta) {
	pos += delta;
}
