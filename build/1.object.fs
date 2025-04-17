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
 vec3 direction;
 vec3 position;

 vec3 ambient;
 vec3 diffuse;
 vec3 specular;

 float constant;
 float linearTerm;
 float quadraticTerm;
};

uniform vec3 ViewPos;

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
	//if fragpos is betweeen of viewPos and and lightPos
	// create line formed by viewPos and LightPos first
	vec3 AB = ViewPos - light.position;
	vec3 AP = FragPos - ViewPos;

	// Check if cross product is close to zero vector (i.e., colinear)
	bool colinear = length(cross(AB, AP)) < 1e-5f;

	// Optional: Check if P is between A and B
	float dot1 = dot(AP, AB);
	float dot2 = dot(AB, AB);
	bool onSegment = colinear && dot1 >= 0.0f && dot1 <= dot2;

	// norm is a vector represent the angle between light ray and fragment
	vec3 norm = normalize(Normal);	// Turn this into unit vector
	vec3 lightDir = onSegment?vec3(0.0):normalize(light.position - FragPos);
	vec3 viewDir = normalize( ViewPos - FragPos);// work
	vec3 reflectDir = reflect(-lightDir, norm);// work
	// when the light source is blocked how to simulate them

	//DIFFUSE
	float diff = max(dot(norm, lightDir), 0.0);// Max() is to forestall negative color
	vec3 diffuse = light.diffuse * diff * texture(material.diffuseMap, TexCoord).rgb;
	//from the vertex shader

	//SPECULAR
	//This time the specular part: We need reflect dir (caculated by dot negate light dir and norm vec), view dir(by normalize fragpos and view pos) to caculate
	// The reflection is supposed to be zero when the face is the same direction of the light

	// Why spec is zero
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), 0.10f);
	vec3 specular = light.specular * spec * texture(material.specularMap, TexCoord).rgb;

	// Inverse something is use 1.0 subtract its value
	// Why the specular with the metal rim texture appear above the box texture??

	// This length is for calculating the distance
	float distance = length(light.position - FragPos);
	float attenuation = 1.0f / (light.constant + light.linearTerm * distance + light.quadraticTerm * (distance * distance));

	ambient *= attenuation;
	diffuse *= attenuation;
	specular *= attenuation;
	
	// Emission vec3 emission = texture(material.emissionMap, TexCoord).rgb;
	vec3 result = ambient + diffuse + specular;

	FragColor = vec4(result, 1.0f);
}

