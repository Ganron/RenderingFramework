#version 450 core
layout(binding = 0) uniform sampler2D tex;

struct Material
{
	vec3 ambientColor;
	vec3 diffuseColor;
	vec3 specularColor;
	float specularExponent;
};

layout(location = 10) uniform Material material;

const vec3 lightAmbient = vec3(0.0,0.0,0.0);
const vec3 lightDiffuse = vec3(1.0f,1.0f,1.0f);
const vec3 lightSpecular = vec3(1.0f,1.0f,1.0f);
const vec3 lightDirection = vec3(0.0f,-1.0f,-1.0f);

in VertShaderOut
{
	vec3 viewDir;
	vec3 normal;
	vec2 texCoords;
} fsIn;

out vec4 color;

void main(void)
{
	vec3 lightDir = -normalize(lightDirection);
	vec3 viewDir = normalize(fsIn.viewDir);
	vec3 normal = normalize(fsIn.normal);

	vec3 ambient = material.ambientColor*lightAmbient;
	vec3 diffuse = max(dot(normal,lightDir), 0.0) * material.diffuseColor * lightDiffuse * texture(tex,fsIn.texCoords).rgb;

	vec3 halfVector = normalize(lightDir+viewDir);
	vec3 specular = pow(max(dot(normal,halfVector),0.0),material.specularExponent) * material.specularColor * lightSpecular;

	color = vec4(ambient+diffuse+specular, 1.0);
}