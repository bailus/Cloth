/*
 * Constraint.h
 *
 *  Created on: 15/10/2014
 *      Author: sam
 */

#ifndef CONSTRAINT_H_
#define CONSTRAINT_H_

#include "Includes.h"
#include "Particle.h"

class Constraint {
public:
	Constraint(Particle *p1, Particle *p2);
	virtual ~Constraint();

	void satisfy();
	void display();

private:
	Particle *p1, *p2;
	float distance;
};

#endif /* CONSTRAINT_H_ */
