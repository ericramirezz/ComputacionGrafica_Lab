#version 330 core
in vec3 ourColor;

out vec4 color;

void main()
{
//Usamos el color dinámico y 1.0 para opacidad completa
	color = vec4(ourColor, 1.0f);
}