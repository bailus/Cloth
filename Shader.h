/*
 * Shader.h
 *
 *  Created on: 21/09/2014
 *      Author: sam
 */

#ifndef SHADER_H_
#define SHADER_H_

#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>

#define GLM_FORCE_RADIANS
#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"

class Shader {
public:
	GLuint
		vertShader, fragShader,
		program,

		ModelLocation,
		ViewLocation,
		ProjectionLocation,

		VertexLocation,
		NormalLocation;

	void setModelMatrix(glm::mat4);
	void setViewMatrix(glm::mat4);
	void setProjectionMatrix(glm::mat4);

	Shader(char* vertSource, char* fragSource);
	virtual ~Shader();

	void use();
};

#endif /* SHADER_H_ */
