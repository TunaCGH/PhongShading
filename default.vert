#version 330 core
// input data from VAO and VBO
layout (location = 0) in vec3 aPos; 
layout (location = 1) in vec3 aNormal;



out vec3 FragPos;
out vec3 Normal;

uniform mat4 model;
uniform mat4 camMatrix; // projection * view


void main()
{
    //find vertex position in world space
    FragPos = vec3(model * vec4(aPos, 1.0));
    
    //find vertex normal in world space
    Normal = mat3(transpose(inverse(model))) * aNormal;


    gl_Position = camMatrix * model * vec4(aPos, 1.0);
}

