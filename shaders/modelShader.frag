#version 330 core
out vec4 FragColor;

in vec3 Normal;
in vec3 FragPos;
in vec2 TexCoord;

uniform sampler2D texture_diffuse1;
uniform sampler2D texture_diffuse2;
uniform sampler2D texture_diffuse3;
uniform sampler2D texture_specular1;
uniform sampler2D texture_specular2;
uniform sampler2D texture_specular3;

uniform vec3 viewerPos;

struct Material{
    float shininess;
};
uniform Material material;

struct DirectionLight{
    vec3 color;
    vec3 direction;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};
uniform DirectionLight directionLight;

vec3 calculateDirectionLight(DirectionLight light,vec3 normal,vec3 viewDir,vec3 diffuseMapColor,vec3 specularMapColor);

void main()
{
    vec3 result=vec3(0.f);
    
    vec3 normal=normalize(Normal);
    vec3 viewDir=normalize(viewerPos-FragPos);
    vec3 diffuseMapColor=vec3(0.f);
    vec3 specularMapColor=vec3(0.f);
    diffuseMapColor+=vec3(texture(texture_diffuse1,TexCoord).rgb);
    diffuseMapColor+=vec3(texture(texture_diffuse2,TexCoord).rgb);
    diffuseMapColor+=vec3(texture(texture_diffuse3,TexCoord).rgb);
    specularMapColor+=vec3(texture(texture_specular1,TexCoord).rgb);
    specularMapColor+=vec3(texture(texture_specular2,TexCoord).rgb);
    specularMapColor+=vec3(texture(texture_specular3,TexCoord).rgb);
    
    result+=calculateDirectionLight(directionLight,normal,viewDir,diffuseMapColor,specularMapColor);
    FragColor=vec4(vec3(0,0.5,1.f),1.f);
}

vec3 calculateDirectionLight(DirectionLight light,vec3 normal,vec3 viewDir,vec3 diffuseMapColor,vec3 specularMapColor){
    vec3 ambient=light.ambient*diffuseMapColor;
    
    vec3 lightDir=normalize(-light.direction);
    float diff=max(dot(lightDir,normal),0.f);
    vec3 diffuse=light.diffuse*diff*diffuseMapColor;
    
    vec3 halfVec=normalize(viewDir+lightDir);
    float spec=pow(max(dot(normal,halfVec),0.f),material.shininess);
    vec3 specular=light.specular*spec*specularMapColor;
    
    return ambient+diffuse+specular;
}
