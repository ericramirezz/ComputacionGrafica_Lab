#version 330 core

struct Material
{
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
};

struct Light
{
    vec3 position;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoords;

out vec4 color;

uniform vec3 viewPos;
uniform Material material;

// El arreglo de luces debe ir AQUÍ, DESPUÉS de que definimos qué es un "Light"
uniform Light lights[2]; 

uniform sampler2D texture_diffusse;

void main()
{
    vec3 norm = normalize(Normal);
    vec3 viewDir = normalize(viewPos - FragPos);
    
    // Aquí guardaremos la suma de ambas luces
    vec3 result = vec3(0.0); 

    // Calculamos el impacto de cada luz y lo sumamos
    for(int i = 0; i < 2; i++)
    {
        // Ambient
        vec3 ambient = lights[i].ambient * material.diffuse;
        
        // Diffuse
        vec3 lightDir = normalize(lights[i].position - FragPos);
        float diff = max(dot(norm, lightDir), 0.0);
        vec3 diffuse = lights[i].diffuse * diff * material.diffuse;
        
        // Specular
        vec3 reflectDir = reflect(-lightDir, norm);
        float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
        vec3 specular = lights[i].specular * (spec * material.specular);
        
        result += (ambient + diffuse + specular);
    }
    
    color = vec4(result, 1.0f) * texture(texture_diffusse, TexCoords);
}