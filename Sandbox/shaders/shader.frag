#version 330 core

uniform vec4 ourColor;
uniform sampler2D u_Texture;


in vec2 v_TexCoord;
out vec4 color;

void main()
{
	//vec4 text = texture(u_Texture,v_TexCoord);
	vec4 text = ourColor;
	color = text;
}