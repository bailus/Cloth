#include "Triangle.h"

Triangle::Triangle(Particle* p1, Particle* p2, Particle* p3) {

	particles[0] = p1;
	particles[1] = p2;
	particles[2] = p3;

}

void Triangle::display() {

	for (int i = 0; i < 3; i++) {
		glTexCoord2fv(glm::value_ptr(particles[i]->texCoord));
		glNormal3fv(glm::value_ptr(particles[i]->normal));
		glVertex3fv(glm::value_ptr(particles[i]->pos));
	}
}

Triangle::~Triangle() {
}

