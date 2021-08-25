#shader vertex

#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTex;

uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;

out vec3 FragPos;
out vec3 normal;
out vec2 texCoord;

void main() {

	FragPos = vec3(model * vec4(aPos, 1.f));
	gl_Position = proj * view * model * vec4(aPos, 1.f);
	normal = mat3(transpose(inverse(model))) * aNormal;
	texCoord = aTex;

}

#shader fragment
#version 330 core

struct Material {

	sampler2D texture_diffuse0;
	sampler2D texture_specular0;

};

struct PointLight {

	vec3 position;
	vec3 color;

	float a;
	float b;

	float ambient;
	float diffuse;
	float specular;

};

struct DirLight {

	vec3 direction;
	
	float ambient;
	float diffuse;
	float specular;

};

struct SpotLight {

	vec3 position;
	vec3 direction;

	float outerCone;	// Needs to be in cosine values
	float innerCone;	// Needs to be in cosine values

	float ambient;
	float diffuse;
	float specular;

};

vec4 calcPointLight(PointLight pointLight);
vec4 calcDirectLight(DirLight dirLight);
vec4 calcSpotLight(SpotLight spotLight);

in vec3 FragPos;
in vec3 normal;
in vec2 texCoord;

uniform vec3 viewPos;

out vec4 FragColor;

uniform Material material;
uniform DirLight dirLight;
uniform PointLight pointLight;
uniform SpotLight spotLight;

void main() {

	FragColor = calcPointLight(pointLight);

}

vec4 calcPointLight(PointLight pointLight) {

	vec3 lightVec = pointLight.position - FragPos;

	// Simulates darkening over distance
	float dist = length(lightVec);
	float a = pointLight.a;
	float b = pointLight.b;
	float inten = 1.f / (a * dist * dist + b * dist + 1.f);

	// ambient
	float ambient = pointLight.ambient;

	// diffuse
	vec3 normal = normalize(normal);
	vec3 lightDirection = normalize(lightVec);
	float diff = max(dot(normal, lightDirection), 0.f);
	float diffuse = diff * pointLight.diffuse;

	// speuclar
	float specularLight = pointLight.specular;
	vec3 viewDirection = normalize(viewPos - FragPos);
	vec3 reflectionDirection = reflect(-lightDirection, normal);
	float specAmount = pow(max(dot(viewDirection, reflectionDirection), 0.f), 32);
	float specular = specAmount * specularLight;

	vec4 diffuseLightComponent = texture(material.texture_diffuse0, texCoord);
	float alpha = diffuseLightComponent.w;
	if (alpha < 0.1f) discard;
	diffuseLightComponent *= (diffuse * inten + ambient);
	diffuseLightComponent.w = alpha;		// Set Alpha channel back to 1, cause it got changed in line above

	vec4 specularLightComponent = texture(material.texture_specular0, texCoord);
	alpha = specularLightComponent.w;
	specularLightComponent *= specular * inten;
	specularLightComponent.w = alpha;		// Set Alpha channel back to 1, cause it got changed in line above

	return  (diffuseLightComponent + specularLightComponent) * vec4(pointLight.color, 1.f);

}

vec4 calcDirectLight(DirLight dirLight) {

	// ambient
	float ambient = dirLight.ambient;

	// diffuse
	vec3 normal = normalize(normal);
	vec3 lightDirection = normalize(dirLight.direction);
	float diff = max(dot(normal, lightDirection), 0.f);
	float diffuse = diff * pointLight.diffuse;

	// speuclar
	float specularLight = dirLight.specular;
	vec3 viewDirection = normalize(viewPos - FragPos);
	vec3 reflectionDirection = reflect(-lightDirection, normal);
	float specAmount = pow(max(dot(viewDirection, reflectionDirection), 0.f), 16);
	float specular = specAmount * specularLight;

	vec4 diffLightComponent = texture(material.texture_diffuse0, texCoord);
	float alpha = diffLightComponent.w;
	if (alpha < 1.f) discard;
	diffLightComponent *= ambient + diffuse;
	diffLightComponent.w = alpha;		// Alpha channel need to be 1

	vec4 specLightComponent = texture(material.texture_specular0, texCoord);
	alpha = specLightComponent.w;
	specLightComponent *= specular;
	specLightComponent.w = alpha;

	return diffLightComponent + specLightComponent;

}

vec4 calcSpotLight(SpotLight spotLight) {

	float outerCone = spotLight.outerCone;
	float innerCone = spotLight.innerCone;
	
	// ambient
	float ambient = spotLight.ambient;

	// diffuse
	vec3 normal = normalize(normal);
	vec3 lightDirection = normalize(spotLight.position - FragPos);
	float diff = max(dot(normal, lightDirection), 0.f);
	float diffuse = diff * pointLight.diffuse;

	// speuclar
	float specularLight = spotLight.specular;
	vec3 viewDirection = normalize(viewPos - FragPos);
	vec3 reflectionDirection = reflect(-lightDirection, normal);
	float specAmount = pow(max(dot(viewDirection, reflectionDirection), 0.f), 32);
	float specular = specAmount * specularLight;

	// calc spot light angles
	float angle = dot(spotLight.direction, -lightDirection);
	float inten = clamp((angle - outerCone) / (innerCone - outerCone), 0.f, 1.f);

	vec4 diffuseLightComponent = texture(material.texture_diffuse0, texCoord);
	float alpha = diffuseLightComponent.w;
	if (alpha < 1.f) discard;
	diffuseLightComponent *= diffuse * inten + ambient;
	diffuseLightComponent.w = alpha;

	vec4 specLightComponent = texture(material.texture_specular0, texCoord);
	alpha = specLightComponent.w;
	specLightComponent *= specular * inten;
	specLightComponent.w = alpha;

	return diffuseLightComponent + specLightComponent;

}