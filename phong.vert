#version 130

uniform mat4 Model;
uniform mat4 View;
uniform mat4 Projection;

varying vec3 normalVec;
varying vec3 lightVec;

varying vec2 texCoord;

void main() {
	texCoord = gl_MultiTexCoord0.st;
	
	mat4 MV = View * Model;

	normalVec = (MV * vec4(gl_Normal, 0)).xyz;
	lightVec = (MV * gl_LightSource[0].position).xyz;
	
	gl_Position = Projection * MV * gl_Vertex;
}