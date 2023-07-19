#version 420 core
out vec4 FragColor;

in VS_OUT {
    vec2 texCoord;
	vec3 FragPos;
	vec3 Normal;
} fs_in;

struct Material {
    vec4 ambient;
    vec4 diffuse;
    vec4 specular;
    float shininess;
};

struct DirLight
{
    vec3 direction;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
};
  
uniform Material material;
uniform DirLight dirLight;
uniform vec3 viewPos;

uniform sampler2D texture_diffuse1;
uniform bool use_diffuse_texture;

vec3 CalcDirLight(DirLight light,vec3 normal, vec3 viewDir);

void main()
{
    vec3 norm = normalize(fs_in.Normal);
    vec3 viewDir = normalize(viewPos - fs_in.FragPos);
    vec3 result = CalcDirLight(dirLight, norm, viewDir);
    FragColor = vec4(result, 1.0);
}

vec3 CalcDirLight(DirLight light,vec3 normal, vec3 viewDir)
{
    vec3 lightDir = normalize(-light.direction);

    float diff = max(dot(normal,lightDir),0.0);

    vec3 halfv = normalize(viewDir+lightDir);
    float spec = pow(max(dot(normal,halfv),0.0),light.shininess);

    vec4 diffuse_texture = vec4(0.0);
    if(use_diffuse_texture){
        diffuse_texture = texture(texture_diffuse1, fs_in.texCoord);
    }     

    vec3 diffuse_blend  = diffuse_texture.rgb * diffuse_texture.a + (1 - diffuse_texture.a) * material.diffuse.rgb;

    vec3 ambient = light.ambient * diffuse_blend;
    vec3 diffuse = light.diffuse * diff * diffuse_blend;
    vec3 specular = light.specular *spec* diffuse_blend;
    return ambient+diffuse+specular;
}
