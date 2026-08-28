#version 330 core
out vec4 FragColor;


in vec3 FragPos;
in vec3 Normal;

uniform vec3 lightPos; 
uniform vec3 viewPos; 
uniform vec3 lightColor;
uniform vec3 objectColor;


void main()
{
    //env ligth
    float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * lightColor;



    //diffuse
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);

    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;
    


    // Specular 
    float specularStrength = 0.6;                   // reflection power
    vec3 viewDir = normalize(viewPos - FragPos);    // on the dot
    vec3 reflectDir = reflect(-lightDir, norm);     // reflection direction

    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 300); 
    vec3 specular = specularStrength * spec * lightColor;  




    // 
    vec3 result = (ambient + diffuse + specular) *objectColor;
    FragColor = vec4(result, 1.0);
}