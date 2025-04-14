#version 330 core
//Set the output color vector first
out vec4 FragColor;

struct Material{
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

uniform vec3 ObjectColor;
uniform vec3 lightColor;

uniform Material material;
uniform Light light;

in vec3 FragPos;
in vec3 Normal;

void main()
{
	//AMBIENT
	vec3 ambient = light.ambient * material.ambient;

	//=========================================================
	// Light direction is the difference between lightPos and Fragment Pos
	vec3 lightDir = normalize(light.position - FragPos);
	//norm is a vector represent the angle between light ray and fragment
	//from the vertex shader
	vec3 norm = normalize(Normal);	// Turn this into unit vector

	//DIFFUSE
	float diff = max(dot(norm, lightDir), 0.0);// Max() is to forestall negative color
	vec3 diffuse = (diff * material.diffuse) * light.diffuse;

	//SPECULAR
	//This time the specular part: We need reflect dir (caculated by dot negate light dir and norm vec), view dir(by normalize fragpos and view pos) to caculate
	vec3 viewDir = normalize(viewPos - FragPos);
	vec3 reflectDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
	vec3 specular = spec * material.specular * light.specular;

	// Why remove the *ObjectColor part resulted in better color this case???
	vec3 result = (ambient + diffuse + specular);
	FragColor = vec4(result, 1.0);
}