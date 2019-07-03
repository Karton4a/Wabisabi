#version 330 core

#include "structs/material.prep"
uniform vec4 ourColor;
uniform vec3 LightPosition;
uniform vec3 LightColor;
uniform Material material;
//uniform sampler2D diffuseTexture;
//uniform sampler2D SpecularTexture;
out vec4 color;

in vec3 Normal;
in vec3 FragmentPosition;
in mat3 View;
in vec2 v_TextureCoord;

void main()
{
	vec3 ambientColor = vec3(texture(material.diffuse,v_TextureCoord));//vec3(1.0f, 0.5f, 0.31f);
    vec3 ambient = ambientColor * vec3(0.1f);

    // Diffuse
	vec3 diffuseColor = vec3(texture(material.diffuse,v_TextureCoord));
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize((View*LightPosition) - FragmentPosition);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diffuseColor *diff * vec3(0.5f);
    
    // Specular
    vec3 specularColor = vec3(texture(material.specular,v_TextureCoord));
    vec3 viewDir = normalize(vec3(0.f) - FragmentPosition);
    vec3 reflectDir = reflect(-lightDir, norm);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0),material.shiness);
    vec3 specular = specularColor * spec * LightColor; 

	vec3 res = (ambient + diffuse +  specular);
	color = vec4(res,1.f);
}
/*vec3 PhongLight(vec3 fragmentPosition,vec3 normal,vec3 lightPosition,vec3 cameraPosition,vec3 lightColor)
{
	return vec3(1.f);
}*/