#version 460 core

out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D ourTexture;

uniform vec3 objectColor;
uniform vec3 lightColor;

void main()
{
    //FragColor = texture(ourTexture, TexCoords);
	FragColor = vec4(lightColor * objectColor, 1.0);
}