/*
 * Floor.h
 *
 *  Created on: 18/10/2014
 *      Author: sam
 */

#ifndef CUBE_H_
#define CUBE_H_

#include "Thing.h"

class Floor: public Thing {
public:
	Floor(glm::vec3 position, float width, float depth, glm::vec4 color);
	virtual ~Floor();

	void collision(std::vector<Particle> *particles);
	void display(Shader *shader);
	void move(glm::vec3 v);

private:
	float width, depth;
	glm::vec3 pos;
	glm::vec4 color;

	float
		leftX,
		rightX,
		backZ,
		frontZ;

};

#endif /* CUBE_H_ */
