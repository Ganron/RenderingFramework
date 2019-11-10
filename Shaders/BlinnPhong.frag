#version 450 core
#define MAX_POINT_LIGHTS 10
#define MAX_SPOT_LIGHTS 10

layout(binding = 0) uniform sampler2D tex;

struct Material
{
	vec3 ambientColor;
	vec3 diffuseColor;
	vec3 specularColor;
	float specularExponent;
};

struct DirLight
{
	vec3 direction;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

struct PointLight
{
	vec4 position;
	vec4 ambient_constCoeff; //last component is the constant attenuation coefficient
	vec4 diffuse_linearCoeff; //last component it the linear attenuation coefficient
	vec4 specular_quadCoeff; //last component it the qudratic attenuation coefficient
};

struct SpotLight
{
	vec4 position_innerCone; //last component is the inner cone angle
	vec4 direction_outerCone; //last component is the outer cone angle
	vec4 ambient_constCoeff; //last component is the constant attenuation coefficient
	vec4 diffuse_linearCoeff; //last component it the linear attenuation coefficient
	vec4 specular_quadCoeff; //last component it the qudratic attenuation coefficient
};

layout(location = 1) uniform mat4 viewMatrix;
layout(location = 10) uniform Material material;
layout(location = 14) uniform bool useDirLight;
layout(location = 15) uniform DirLight  dirLight;

layout(std140, binding = 0) uniform POINT_LIGHTS
{
	PointLight pointLights[MAX_POINT_LIGHTS];
	int numPointLights;
};

layout(std140, binding = 1) uniform SPOT_LIGHTS
{
	SpotLight spotLights[MAX_SPOT_LIGHTS];
	int numSpotLights;
};

in VertShaderOut
{
	vec3 posViewSpace;
	vec3 normal;
	vec2 texCoords;
} fsIn;

out vec4 finalColor;

vec3 ProcessDirLight(vec3 normal, vec3 viewDir);
vec3 ProcessPointLights(vec3 normal, vec3 viewDir);
vec3 ProcessSpotLights(vec3 normal, vec3 viewDir);

void main(void)
{
	vec3 viewDir = normalize(-fsIn.posViewSpace);
	vec3 normal = normalize(fsIn.normal);

	vec3 color = vec3(0.0);
	color += ProcessDirLight(normal, viewDir);
	color += ProcessPointLights(normal,viewDir);
	color += ProcessSpotLights(normal,viewDir);
	finalColor = vec4(color, texture(tex,fsIn.texCoords).a);
}

vec3 ProcessDirLight(vec3 normal, vec3 viewDir)
{
	vec3 color = vec3(0.0);
	if(useDirLight)
	{
		vec3 lightDir = -normalize(mat3(viewMatrix)*dirLight.direction);
		vec3 ambient = material.ambientColor*dirLight.ambient * texture(tex,fsIn.texCoords).rgb;
		vec3 diffuse = max(dot(normal,lightDir), 0.0) * material.diffuseColor * dirLight.diffuse * texture(tex,fsIn.texCoords).rgb;

		vec3 halfVector = normalize(lightDir+viewDir);
		vec3 specular = pow(max(dot(normal,halfVector),0.0),material.specularExponent) * material.specularColor * dirLight.specular;

		color = ambient + diffuse + specular;
	}
	return color;
}

vec3 ProcessPointLights(vec3 normal, vec3 viewDir)
{
	vec3 color = vec3(0.0);
	for(int i = 0; i<numPointLights; i++)
	{
		vec3 lightPosViewSpace = (viewMatrix * pointLights[i].position).xyz;
		vec3 lightDir = normalize(lightPosViewSpace - fsIn.posViewSpace);

		vec3 ambient = material.ambientColor * pointLights[i].ambient_constCoeff.xyz * texture(tex,fsIn.texCoords).rgb;
		vec3 diffuse = max(dot(normal,lightDir), 0.0) * material.diffuseColor * pointLights[i].diffuse_linearCoeff.xyz * texture(tex,fsIn.texCoords).rgb;

		vec3 halfVector = normalize(lightDir+viewDir);
		vec3 specular = pow(max(dot(normal,halfVector),0.0),material.specularExponent) * material.specularColor * pointLights[i].specular_quadCoeff.xyz;

		float dist = length(lightPosViewSpace - fsIn.posViewSpace);
		float attenuation = 1.0f / (pointLights[i].ambient_constCoeff.w + pointLights[i].diffuse_linearCoeff.w*dist + pointLights[i].specular_quadCoeff.w*dist*dist);

		color+= (ambient + diffuse + specular)*attenuation;
	}
	return color;
}

vec3 ProcessSpotLights(vec3 normal, vec3 viewDir)
{
	vec3 color = vec3(0.0);
	for(int i = 0; i<numSpotLights; i++)
	{
		vec3 lightPosViewSpace = (viewMatrix * vec4(spotLights[i].position_innerCone.xyz,1.0)).xyz;
		vec3 lightDir = normalize(lightPosViewSpace - fsIn.posViewSpace);

		vec3 ambient = material.ambientColor * spotLights[i].ambient_constCoeff.xyz * texture(tex,fsIn.texCoords).rgb;
		vec3 diffuse = max(dot(normal,lightDir),0.0) * material.diffuseColor * spotLights[i].diffuse_linearCoeff.xyz * texture(tex,fsIn.texCoords).rgb;

		vec3 halfVector = normalize(lightDir+viewDir);
		vec3 specular = pow(max(dot(normal,halfVector),0.0),material.specularExponent) * material.specularColor * spotLights[i].specular_quadCoeff.xyz;

		float dist = length(lightPosViewSpace - fsIn.posViewSpace);
		float attenuation = 1.0f / (spotLights[i].ambient_constCoeff.w + spotLights[i].diffuse_linearCoeff.w*dist + spotLights[i].specular_quadCoeff.w*dist*dist);

		float currentAngle = dot(lightDir,-normalize(mat3(viewMatrix)*spotLights[i].direction_outerCone.xyz));
		float lowerEdge = cos(spotLights[i].direction_outerCone.w);
		float upperEdge = cos(spotLights[i].position_innerCone.w);
		float finalValue = smoothstep(lowerEdge,upperEdge,currentAngle);
		
		color+=(ambient+diffuse+specular) * attenuation * finalValue;
	}
	return color;
}