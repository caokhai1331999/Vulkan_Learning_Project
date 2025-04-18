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
 // Inherent component
 vec3 direction;
 vec3 position;

 // For Phong Reflection
 vec3 ambient;
 vec3 diffuse;
 vec3 specular;

 // For attenuation (Point Light)
 float constant;
 float linearTerm;
 float quadraticTerm;

 // For spotlight effect
 vec3 spotDir;
 float cutOff;// spotlight area defining angle(Phi) maybe with the different name such as cutoff
 // Now the smooth/soft edge effect
 float outerCutOff;
};

uniform vec3 ViewPos;

uniform Material material;
uniform Light light;

in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoord;

void main()
{	 

	//=========================================================
	//if fragpos is betweeen of viewPos and and lightPos
	// create line formed by viewPos and LightPos first
	vec3 AB = ViewPos - light.position;//Light Dir
	vec3 AP = FragPos - ViewPos;//View Dir

	// Check if cross product is close to zero vector (i.e., colinear)
	bool colinear = length(cross(AB, AP)) < 1e-5f;

	// Optional: Check if P is between A and B
	float dot1 = dot(AP, AB);
	float dot2 = dot(AB, AB);
	bool onSegment = colinear && dot1 >= 0.0f && dot1 <= dot2;

	// norm is a vector represent the angle between light ray and fragment
	vec3 norm = normalize(Normal);	// Turn this into unit vector

	// Directional Light(No light source position)
	// vec3 lightDir = normalize(-light.direction);

	// FOR POINT LIGHT
	// The direction from fragment to light source
	vec3 lightDir = onSegment?vec3(0.0):normalize(light.position - FragPos);

	vec3 viewDir = normalize( ViewPos - FragPos);// work
	vec3 reflectDir = reflect(-lightDir, norm);// work
	// when the light source is blocked how to simulate them

	vec3 ambient;

	float diff;
	vec3 diffuse;  

	float spec;
	vec3 specular;

	float distance;
	float attenuation;

	vec3 emission;
	vec3 result;

	// This is the cosine value of theta angle
	// float theta = dot(lightDir, (normalize(-light.direction)));

	// if(theta > light.cutOff)
	// Cause cos value of the angle is inversed( opposite) with angle value so this is when the theta is smaller than the cutoff
	// {
	// Smooth edge calculation
	// float epsilon = light.cutOff - light.outerCutOff;
	// float intensity = clamp((theta - light.outerCutOff)/epsilon, 0.0, 1.0);

	// Apply the spotlight effect here
	// Ambient
	 ambient = light.ambient * texture(material.diffuseMap, TexCoord).rgb;

	//DIFFUSE
	diff = max(dot(norm, lightDir), 0.0);// Max() is to forestall negative color
	diffuse = light.diffuse * diff * texture(material.diffuseMap, TexCoord).rgb;
	//from the vertex shader

	//SPECULAR
	//This time the specular part: We need reflect dir (caculated by dot negate light dir and norm vec), view dir(by normalize fragpos and view pos) to caculate
	// The reflection is supposed to be zero when the face is the same direction of the light

	// Why spec is zero
	spec = pow(max(dot(viewDir, reflectDir), 0.0), 0.10f);
	specular = light.specular * spec * texture(material.specularMap, TexCoord).rgb;

	// Inverse something is use 1.0 subtract its value
	// Why the specular with the metal rim texture appear above the box texture??

	// This length is for calculating the distance
	distance = length(light.position - FragPos);
	attenuation = 1.0f / (light.constant + light.linearTerm * distance + light.quadraticTerm * (distance * distance));

	ambient *= attenuation;

	diffuse *= attenuation;
	//diffuse *= intensity;
	specular *= attenuation;
	//specular *= intensity;	
	// Emission vec3 emission = texture(material.emissionMap, TexCoord).rgb;
	result = ambient + diffuse + specular;
	  
	//} else {
	//  ambient = light.ambient * texture(material.diffuseMap, TexCoord).rgb;
	//  result = ambient;
	//}

	FragColor = vec4(result, 1.0f);
}

