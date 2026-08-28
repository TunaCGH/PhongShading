#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm/glm.hpp>
#include <glm/glm/gtc/matrix_transform.hpp>
#include <glm/glm/gtc/type_ptr.hpp>
#include "Shader.h"

class Camera
{
public:
    // define camera position in 3D space 
    glm::vec3 Position;

	// default orientation declaration   
    glm::vec3 Orientation = glm::vec3(0.0f, 0.0f, -1.0f);//camera direction 
    glm::vec3 Up = glm::vec3(0.0f, 1.0f, 0.0f);//define which is up


    // camera frame size 
    int width;
    int height;

    // constructor - get the input
    Camera(int width, int height, glm::vec3 position);

    //compute(View * Projection) and send to Shader
    void Matrix(float FOVdeg, float nearPlane, float farPlane, Shader& shader, const char* uniform);
};

