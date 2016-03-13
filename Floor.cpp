/*
 * Floor.cpp
 *
 *  Created on: 18/10/2014
 *      Author: sam
 */

#include "Floor.h"

Floor::Floor(glm::vec3 position, float width, float depth, glm::vec4 color) {
	this->pos = position;
	this->width = width;
	this->depth = depth;
	this->color = color;

	leftX = pos.x - (width/2),
	rightX = pos.x + (width/2),
	backZ = pos.z - (depth/2),
	frontZ = pos.z + (depth/2);
}

Floor::~Floor() {
	// TODO Auto-generated destructor stub
}



void Floor::collision(std::vector<Particle> *particles) {

	for (std::vector<Particle>::size_type i = 0; i < particles->size(); i++) {

		glm::vec3 posP = (*particles)[i].pos;
		if (posP.y <= pos.y)
			(*particles)[i].pos += glm::vec3(0, pos.y - posP.y, 0);
	}
}

void Floor::display(Shader *shader) {
	shader->setModelMatrix(glm::mat4());
	glColor3fv(glm::value_ptr(color));

	glBegin(GL_QUADS);

	float normal[] = {0,1,0};
	// lx,bz rx,bz
	// lx,fz rx,fz

	glNormal3fv(normal);
	glVertex3f(leftX, pos.y, backZ);
	glNormal3fv(normal);
	glVertex3f(rightX, pos.y, backZ);
	glNormal3fv(normal);
	glVertex3f(rightX, pos.y, frontZ);
	glNormal3fv(normal);
	glVertex3f(leftX, pos.y, frontZ);

	glEnd();
}

void Floor::move(glm::vec3 v) {
	(void)v;
}
