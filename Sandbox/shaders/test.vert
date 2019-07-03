#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;

uniform mat4 u_Proj;
uniform mat4 u_View;
uniform mat4 u_Model;

#include "test.prep"


out vec3 Normal;
out vec3 FragmentPosition;
out mat3 View;
void main()
{
	gl_Position =  u_Proj * u_View * u_Model * vec4(position.x, position.y, position.z, 1.0);

	FragmentPosition = vec3(u_View*u_Model * vec4(position, 1.0));
	Normal = mat3(transpose(inverse(u_View*u_Model)))*normal;
	View = mat3(u_View);
}