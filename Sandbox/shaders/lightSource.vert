#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normals;

uniform mat4 u_Proj;
uniform mat4 u_View;
uniform mat4 u_Model;



void main()
{
	gl_Position =  u_Proj * u_View * u_Model * vec4(position.x, position.y, position.z, 1.0);
}