#version 420 core
out vec4 FragColor;

in VS_OUT {
    vec2 texCoord;
	vec3 FragPos;
} fs_in;

struct Material {
    vec4 ambient;
    vec4 diffuse;
    vec4 specular;
    float shininess;
}; 
  
uniform Material material;

uniform sampler2D texture_diffuse1;

void main()
{
    //FragColor = texture(texture_diffuse1, fs_in.texCoord);
    FragColor = vec4(material.diffuse.rgb, 1.0);
}