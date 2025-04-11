#version 330 core
// aPos is the position of each verticle that is in the bound VAO, isn't it
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;

in vec3 FragPos;

uniform vec3 lightPos;
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec3 Normal;

void main()
{
	vec3 norm = normalize(Normal);
	vec3 lightDir = normalize(lightPos - FragPos);

	gl_Position = projection * view * model * vec4(aPos, 1.0f);
	Normal = aNormal;
}