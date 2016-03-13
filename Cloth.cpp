/*
 * Cloth.cpp
 *
 *  Created on: 15/10/2014
 *      Author: sam
 */

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "Cloth.h"

// width/height:
//		Width/Height in space
// particleWidth, particleHeight:
//		Width/Height in particles
Cloth::Cloth(float width, float height, int particleWidth, int particleHeight, float weight, float damping, glm::mat4 transform) {
	this->particleWidth = particleWidth;
	this->particleHeight = particleHeight;
	this->isTextured = true;
	this->textureID = 0;

	float
		particleSeperationX =  width/particleWidth,
		particleSeperationY = height/particleHeight,
		numParticles = particleWidth * particleHeight,
		particleMass = numParticles/weight,
		particleDamping = 1-damping;

	//Create the particles
	for (int y = 0; y < particleHeight; y++)
		for (int x = 0; x < particleWidth; x++)
			particles.push_back(Particle(
					glm::vec3(transform * glm::vec4(x*particleSeperationX, -y*particleSeperationY, 0, 1)),
					particleMass, particleDamping,
					glm::vec2((float)x/(particleWidth-1), -(float)y/(particleHeight-1))
			));

	//Create the triangles
	for (int y = 1; y < particleHeight; y++)
		for (int x = 1; x < particleWidth; x++) {
			// p1 - p2
			//  | / |
			// p3 - p4
			Particle
				*p1 = &particles[(y-1)*particleWidth+x-1],
				*p2 = &particles[(y-1)*particleWidth+x],
				*p3 = &particles[y*particleWidth+x-1],
				*p4 = &particles[y*particleWidth+x];

			triangles.push_back(Triangle(p3, p1, p2));
			triangles.push_back(Triangle(p2, p4, p3));
		}

	//Define constraints between the particles
	for (int i = 0; i < numParticles; i++) {
		bool
			leftCol = i%particleWidth == 0,
			rightCol = (i+1)%particleWidth == 0,
			topRow = i < particleWidth,
			topRows = i < particleWidth*2, //top 2 rows
			leftCols = leftCol || (i-1)%particleWidth == 0; //2 leftmost columns

		//vertical (up)
		if (!topRow)
			constraints.push_back(Constraint(
					&particles[i], &particles[i-particleWidth]
			));
		if (!topRows)
			constraints.push_back(Constraint(
					&particles[i], &particles[i-(particleWidth*2)]
			));

		//horizontal (left)
		if (!leftCol)
			constraints.push_back(Constraint(
					&particles[i], &particles[i-1]
			));
		if (!leftCols)
			constraints.push_back(Constraint(
					&particles[i], &particles[i-2]
			));

		//diagonal \  .
		if (!topRow && !leftCol)
			constraints.push_back(Constraint(
					&particles[i], &particles[i-1-particleWidth]
			));
		//diagonal /  .
		if (!topRow && !rightCol)
			constraints.push_back(Constraint(
					&particles[i], &particles[i+1-particleWidth]
			));

	}

	//give the cloth a tiny push in the z direction
	particles[numParticles/2+particleWidth/2].force.z -= 1;

	//Make some points static
	//particles[particleWidth/2].isStatic = true; //top middle
	particles[0].isStatic = true; //top left
	particles[particleWidth-1].isStatic = true; //top right
	//particles[numParticles-particleWidth].isStatic = true; //bottom left
	//particles[numParticles-1].isStatic = true; //bottom right

	//for (int i = 0; i < particleHeight; i++) //left edge
	//	particles[i*particleWidth].isStatic = true;
}

Cloth::~Cloth() {
	// TODO Auto-generated destructor stub
}


//mode:
//		GL_TRIANGLES for solid
//		GL_LINE_LOOP for wireframe
void Cloth::display(GLenum mode) {

	//Bind the texture
	if (isTextured) {
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, textureID);
	}

	//Calculate normals
	for (int y = 0; y < particleHeight; y++)
		for (int x = 0; x < particleWidth; x++) {
			glm::vec3 vy, vx;
			Particle *p = &particles[y*particleWidth+x];

			if (y > 0) vy = particles[(y-1)*particleWidth+x].pos;
			else vy = p->pos;
			if (y < particleHeight) vy -= particles[(particleHeight-1)*particleWidth+x].pos;
			else vy -= p->pos;

			if (x > 0) vx = particles[y*particleWidth+x-1].pos;
			else vx = p->pos;
			if (x < particleWidth-1) vx -= particles[y*particleWidth+x+1].pos;
			else vx -= p->pos;

			p->normal = glm::normalize(glm::cross(vy, vx));
		}

	//Draw the cloth
	glBegin(mode);
	for (std::vector<Triangle>::size_type i = 0; i < triangles.size(); i++)
		triangles[i].display();
	glEnd();

	//Unbind the texture
	if (isTextured) {
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, 0);
	}

}

void Cloth::displayConstraints() {
	for (std::vector<Constraint>::size_type i = 0; i < constraints.size(); i++)
		constraints[i].display();
}

void Cloth::step(float timeStep) {
	//Gravity
	for (std::vector<Particle>::size_type i = 0; i < particles.size(); i++)
		particles[i].force += glm::vec3(0, -0.3, 0) * timeStep;

	//Satisfy constraints
	for (int n = 0; n < 20; n++)
		for (std::vector<Constraint>::size_type i = 0; i < constraints.size(); i++)
			constraints[i].satisfy();

	//Apply forces
	for (std::vector<Particle>::size_type i = 0; i < particles.size(); i++)
		particles[i].step(timeStep);

}

void Cloth::loadTexture(char* filename) {
	GLenum
		texture = GL_TEXTURE0,
		target = GL_TEXTURE_2D;

	//Init the texture storage, and set some parameters.
	glActiveTexture(texture);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glGenTextures(1, &textureID);
	glBindTexture(target, textureID);

	glTexParameteri(target, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(target, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(target, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(target, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	//Load the png file from disk and decode it
	//  (assumes the file is a png with OpenGL-friendly dimensions)
	int imageWidth, imageHeight, comp;
	stbi_set_flip_vertically_on_load(1);
	unsigned char* imageData = stbi_load(filename, &imageWidth, &imageHeight, &comp, STBI_rgb);

	//Load the texture into GL
	glTexImage2D(target, 0, GL_RGB, imageWidth, imageHeight, 0, GL_RGB,
			GL_UNSIGNED_BYTE, imageData);

	isTextured = true;
}
