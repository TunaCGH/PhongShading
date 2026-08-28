#include "Camera.h"

// constructor - get input 
Camera::Camera(int width, int height, glm::vec3 position)
{
    this->width = width;
    this->height = height;
    Position = position;
}

// compute(View * Projection) and send to Shader
void Camera::Matrix(float FOVdeg, float nearPlane, float farPlane, Shader& shader, const char* uniform)
{
	//initialize matrices
    glm::mat4 view = glm::mat4(1.0f);
    glm::mat4 projection = glm::mat4(1.0f);

    // my view orientation
    view = glm::lookAt(Position, Position + Orientation, Up);

	//limit the view sight (FOV, near and far plane.)
    projection = glm::perspective(glm::radians(FOVdeg), (float)width / height, nearPlane, farPlane);
        
    //multiple two matrices 
    shader.SetMat4(uniform, projection * view);
}