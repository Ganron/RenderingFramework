#version 450 core
void main(void)
{
	vec4 positions[]={  vec4(-1.0, -1.0, 0.0, 1.0), 
						vec4(1.0, -1.0, 0.0, 1.0),
						vec4(1.0, 1.0, 0.0, 1.0),

						vec4(-1.0, -1.0, 0.0, 1.0), 
						vec4(1.0, 1.0, 0.0, 1.0),
						vec4(-1.0, 1.0, 0.0, 1.0)};
	gl_Position=positions[gl_VertexID];
}