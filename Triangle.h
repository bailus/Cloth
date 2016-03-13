#ifndef TRIANGLE_H_
#define TRIANGLE_H_

#include "Particle.h"

class Triangle {
public:
	Triangle(Particle* p1, Particle* p2, Particle* p3);
	virtual ~Triangle();
	void display();

	Particle* particles[3];
};

#endif /* TRIANGLE_H_ */
