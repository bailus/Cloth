/*
 * Cloth.h
 *
 *  Created on: 15/10/2014
 *      Author: sam
 */

#ifndef CLOTH_H_
#define CLOTH_H_

#include "Includes.h"
#include "Particle.h"
#include "Constraint.h"
#include "Triangle.h"

class Cloth {
public:
	Cloth(float width, float height, int particleWidth, int particleHeight, float weight, float damping, glm::mat4 transform);
	virtual ~Cloth();

	void loadTexture(char *filename);

	void display(GLenum mode);
	void displayConstraints();
	void step(float timeStep);
	std::vector<Particle> particles;

private:
	std::vector<Constraint> constraints;
	std::vector<Triangle> triangles;
	int particleWidth;
	int particleHeight;

	bool isTextured;
	GLuint textureID;
};

#endif /* CLOTH_H_ */
