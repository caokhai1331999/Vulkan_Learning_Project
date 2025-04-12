#version 330 core
//Set the output color vector first
out vec4 FragColor;

const float ambientStrength = 0.1;

uniform vec3 ObjectColor;
uniform vec3 lightColor;
uniform vec3 lightPos;

in vec3 FragPos;
in vec3 Normal;

void main()
{
	vec3 ambient = lightColor * ambientStrength;
	//=========================================================
	// Light direction is the difference between lightPos and Fragment Pos
	vec3 lightDir = normalize(lightPos - FragPos);
	//norm is a vector represent the angle between light ray and fragment
	//from the vertex shader
	vec3 norm = normalize(Normal);	// Turn this into unit vector
	float diff = max(dot(norm, lightDir), 0.0);// Max() is to forestall negative color

	vec3 diffuse = diff * lightColor;
	vec3 result = (ambient + diffuse) * ObjectColor;
	FragColor = vec4(result, 1.0);
}