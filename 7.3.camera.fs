#version 330 core
out vec4 FragColor;

in vec2 TexCoord;

// texture samplers
uniform sampler2D texture1;


const float near = 0.1f;
const float far = 100.0;

float linearizeDepth(float depth){
      float ndc = depth * 2.0 - 1.0;// Back to NDC
      return (2.0 * near * far)/(far + near - ndc * (far - near));
      // This will adjust the depth value between far and near one
}

void main()
{
	// linearly interpolate between both textures (80% container, 20% awesomeface)
	//FragColor = mix(texture(texture1, TexCoord), texture(texture2, vec2(1.0 - TexCoord.x, TexCoord.y)), 0.2);
	//FragColor = texture(texture1, TexCoord);

	float depth = linearizeDepth(gl_FragCoord.z) / far;// device by far for demonstration
	FragColor = vec4(vec3(depth), 1.0) + texture(texture1, TexCoord);
}