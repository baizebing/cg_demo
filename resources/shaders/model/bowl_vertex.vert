#version 420 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;

out VS_OUT {
    vec2 texCoord;
	vec3 FragPos;
} vs_out;

uniform mat4 matModel;
uniform mat4 matView;
uniform mat4 matProjection;

void main()
{
	vs_out.FragPos = vec3( matModel * vec4(aPos, 1.0));
	gl_Position = matProjection * matView * vec4(vs_out.FragPos, 1.0);
	vs_out.texCoord = aTexCoord;
}