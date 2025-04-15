#version 330 core

//Set the output color vector first

out vec4 FragColor;

struct Material{
// Ambient will be the same even with change in input
   sampler2D diffuseMap; 
   sampler2D specularMap; 
   sampler2D emissionMap; 

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
	vec3 ambient = light.ambient * (texture(material.diffuseMap, TexCoord));

	//=========================================================
	// Light direction is the difference between lightPos and Fragment Pos
	vec3 lightDir = normalize(light.position - FragPos);
	//norm is a vector represent the angle between light ray and fragment
	//from the vertex shader
	vec3 norm = normalize(Normal);	// Turn this into unit vector

	//DIFFUSE
	float diff = max(dot(norm, lightDir), 0.0);// Max() is to forestall negative color
	vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuseMap, TexCoord));

	//SPECULAR
	//This time the specular part: We need reflect dir (caculated by dot negate light dir and norm vec), view dir(by normalize fragpos and view pos) to caculate
	vec3 viewDir = normalize(viewPos - FragPos);
	vec3 reflectDir = reflect(-lightDir, norm);

	float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);

	//On working
	//vec3 mixLayer = mix(texture(material.emissionMap, TexCoord), texture(material.emissionMap, TexCoord))

	vec3 specular = light.specular * spec * vec3(texture(material.specularMap, TexCoord));

	// Inverse something is use 1.0 subtract its value
	// Why remove the *ObjectColor part resulted in better color this case???

	// How to decide order of overlayed texture
	vec3 result = (ambient + diffuse + emission + specular);
	FragColor = vec4(result, 1.0) ;
}