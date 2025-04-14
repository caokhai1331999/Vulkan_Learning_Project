#version 330 core

uniform vec3 lightColor;
out vec4 FragColor;

void main()
{
 // Set all color to white
  FragColor = vec4(lightColor, 1.0f);
}