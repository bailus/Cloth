#version 130

varying vec3 lightVec;
varying vec3 normalVec;

varying vec2 texCoord;
uniform sampler2D textureSampler;

void main () {
	
	vec3 N = normalize(normalVec);
	vec3 L = normalize(lightVec);
	vec4 texColor = texture(textureSampler, texCoord);
	
	float NdotL = max(dot(N, L), 0);
	
	// Directional Light
	vec4 color = NdotL * gl_LightSource[0].diffuse;
	
	gl_FragColor = mix(texColor * color, texColor, 0.2);
}