#version 450 core
layout(binding = 0 )uniform sampler2D tex;
out vec4 color;
void main(void)
{
	//color = texture(tex, gl_FragCoord.xy / textureSize(tex,0));
	//color=texelFetch(tex, ivec2(gl_FragCoord.xy), 0);
	color = vec4(0.0, 0.0 ,1.0 ,1.0);
}