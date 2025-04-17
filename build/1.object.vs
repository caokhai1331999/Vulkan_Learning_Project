#version 330 core

// aPos is the position of each verticle that is in the bound VAO, isn't it

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoord;


uniform vec3 lightPos;
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec3 Normal;
out vec3 FragPos;
out vec2 TexCoord;
out float distance;

void main()
{
	gl_Position = projection * view * model * vec4(aPos, 1.0f);

	//aPos is the vertex position so the Fragment position is
	//the dot product of model and vertex Position (plus two vector)
	// This is to create a world space coor of fragment
	FragPos = vec3( view *(model *vec4(aPos, 1.0f)));
	//distance = root(pow(FragPos.x - lightPos.x, 2) + pow(FragPos.y - lightPos.y, 2)+ pow(FragPos.z - lightPos.z, 2));

	Normal = mat3(transpose(inverse(view * model))) * aNormal;
	TexCoord = aTexCoord;
}
