#version 330 core
//Set the output color vector first
out vec4 FragColor;

uniform vec3 ObjectColor;
uniform vec3 LightColor;
uniform vec3 LightPos;

void main()
{
	const float ambientStrength = 0.1;
	vec3 ambient = LightColor * ambientStrength;

	vec3 result = ambient * ObjectColor;
	FragColor = vec4(result, 1.0f);
}