#version 450 core
layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec2 texCoords;

layout(location = 0) uniform mat4 modelMatrix;
layout(location = 1) uniform mat4 viewMatrix;
layout(location = 2) uniform mat4 projMatrix;

void main(void)
{
	gl_Position = projMatrix*viewMatrix*modelMatrix*vec4(position,1.0);
}