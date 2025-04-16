#version 330 core

//Set the output color vector first

out vec4 FragColor;

struct Material{
// Ambient will be the same even with change in input
   sampler2D emissionMap; 
   sampler2D diffuseMap; 
   sampler2D specularMap; 

   vec3 ambient;
   vec3 diffuse;
   vec3 specular;

   float shininess;
};

struct Light{
 vec3 position;

 vec3 ambient;
 vec3 diffuse;
 vec3 specular;
};

uniform vec3 viewPos;

uniform Material material;
uniform Light light;

in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoord;

void main()
{
	//AMBIENT
	vec3 ambient = light.ambient * texture(material.diffuseMap, TexCoord).rgb;
	
	//=========================================================
	// Light direction is the difference between lightPos and Fragment Pos
	vec3 lightDir = normalize(light.position - FragPos);
	//norm is a vector represent the angle between light ray and fragment
	vec3 norm = normalize(Normal);	// Turn this into unit vector

	//DIFFUSE
	float diff = max(dot(norm, lightDir), 0.0);// Max() is to forestall negative color
	vec3 diffuse = light.diffuse * diff * texture(material.diffuseMap, TexCoord).rgb;
	//from the vertex shader

	//SPECULAR
	//This time the specular part: We need reflect dir (caculated by dot negate light dir and norm vec), view dir(by normalize fragpos and view pos) to caculate
	vec3 viewDir = normalize(viewPos - FragPos);// work
	vec3 reflectDir = reflect(-lightDir, norm);// work
	// Why spec is zero
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), 0.10f);
	vec3 specular = light.specular * spec * texture(material.specularMap, TexCoord).rgb;

	// Inverse something is use 1.0 subtract its value
	// Why the specular with the metal rim texture appear above the box texture??

	// Emission
	vec3 result = ambient +  diffuse + specular;
	vec3 emission = texture(material.emissionMap, TexCoord).rgb;	
	FragColor = vec4(result, 1.0f) + vec4(emission, 1.0f);
}

