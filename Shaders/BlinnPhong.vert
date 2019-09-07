#version 450 core
layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec2 texCoords;

layout(location = 0) uniform mat4 modelMatrix;
layout(location = 1) uniform mat4 viewMatrix;
layout(location = 2) uniform mat4 projMatrix;

out VertShaderOut
{
	vec3 posViewSpace;
	vec3 normal;
	vec2 texCoords;
} vsOut;

void main(void)
{
	mat4 mvMatrix = viewMatrix * modelMatrix;
	vec4 posViewSpace = mvMatrix * vec4(position, 1.0);

	vsOut.posViewSpace = posViewSpace.xyz; 
	vsOut.normal = mat3(mvMatrix) * normal;
	vsOut.texCoords = texCoords;
	
	gl_Position = projMatrix * posViewSpace;
}