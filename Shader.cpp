/*
 * Shader.cpp
 *
 *  Created on: 21/09/2014
 *      Author: sam
 */

#include "Shader.h"


// from textfile.cpp
// simple reading and writing for text files
// www.lighthouse3d.com
char *textFileRead(char *fn) {

	FILE *fp;
	char *content = NULL;

	int count=0;

	if (fn != NULL) {
		fp = fopen(fn,"rt");

		if (fp != NULL) {

      fseek(fp, 0, SEEK_END);
      count = ftell(fp);
      rewind(fp);

			if (count > 0) {
				content = (char *)malloc(sizeof(char) * (count+1));
				count = fread(content,sizeof(char),count,fp);
				content[count] = '\0';
			}
			fclose(fp);
		}
	}
	return content;
}

//adapted from https://www.opengl.org/wiki/Shader_Compilation#Shader_error_handling
void compilerLog(GLuint shader) {
        GLint isCompiled = 0;
        glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);
        if(isCompiled == GL_FALSE) {
                GLint maxLength = 0;
                glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

                //The maxLength includes the NULL character
                GLchar* compiler_log = (GLchar*)malloc(maxLength);
                glGetShaderInfoLog(shader, maxLength, &maxLength, compiler_log);

                printf(compiler_log);
        }
}


//NOTE: assumes glew is initialized
Shader::Shader(char* vertSource, char* fragSource) {
	char *vs = NULL, *fs = NULL;

	// make space, get a handle
	vertShader = glCreateShader(GL_VERTEX_SHADER);
	fragShader = glCreateShader(GL_FRAGMENT_SHADER);

	// read shader files
	vs = textFileRead(vertSource);
	fs = textFileRead(fragSource);

	// attach code to shader
	const char *ff = fs;
	const char *vv = vs;
	glShaderSource(vertShader, 1, &vv,NULL);
	glShaderSource(fragShader, 1, &ff,NULL);

	// after the files have been loaded by GL we don't need them
	free(vs); free(fs);

	// compile
	glCompileShader(vertShader);
	glCompileShader(fragShader);

	// use a “program” handle for your shader
	program = glCreateProgram();

	// attach shader to program
	glAttachShader(program, fragShader);
	compilerLog(fragShader);
	glAttachShader(program, vertShader);
	compilerLog(vertShader);

	// link the program
	glLinkProgram(program);

	// get the indexes of uniform variables in the shaders for later use
	ModelLocation      = glGetUniformLocation(program, "Model");
	ViewLocation       = glGetUniformLocation(program, "View");
	ProjectionLocation = glGetUniformLocation(program, "Projection");

	// get the indexes of vertex attributes in the shaders for later use
	VertexLocation = glGetAttribLocation(program, "Vertex");
	NormalLocation = glGetAttribLocation(program, "Normal");
}

void Shader::setModelMatrix(glm::mat4 m) {
	glUseProgram(program);
	glUniformMatrix4fv(ModelLocation, 1, GL_FALSE, glm::value_ptr(m));
}
void Shader::setViewMatrix(glm::mat4 m) {
	glUseProgram(program);
	glUniformMatrix4fv(ViewLocation, 1, GL_FALSE, glm::value_ptr(m));
}
void Shader::setProjectionMatrix(glm::mat4 m) {
	glUseProgram(program);
	glUniformMatrix4fv(ProjectionLocation, 1, GL_FALSE, glm::value_ptr(m));
}

void Shader::use() {
	glUseProgram(program);
}

Shader::~Shader() {
	glDeleteShader(vertShader);
	glDeleteShader(fragShader);
	glDeleteProgram(program);
}
