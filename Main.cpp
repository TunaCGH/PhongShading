#include <iostream>
#include <vector>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>
#include <glm/glm/glm.hpp>
#include <glm/glm/gtc/matrix_transform.hpp>
#include <glm/glm/gtc/type_ptr.hpp>

#include "Shader.h"
#include "Mesh.h"
#include "Vertex.h"
#include "Camera.h"


#include "data.h"
#include "Spheredata.h"

int main() {
    // initialize the GLFW library and set window hints
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);




    // create the window
    GLFWwindow* window = glfwCreateWindow(800, 800, "PhongShader Framework", NULL, NULL);
    if (window == NULL) {
        std::cout << "damn it, failed GLFW window creation :((( \n";
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    gladLoadGL();
    glViewport(0, 0, 800, 800);
    glEnable(GL_DEPTH_TEST);



    // initialize Shader
    Shader shaderProgram("default.vert", "default.frag");

	//camera initialization
    Camera camera(800, 800 , glm::vec3(0.0f, 0.0f, 5.0f));

	// define vertices and indices for the object
    std::vector<Vertex> vertices;
    std::vector<GLuint> indices;
    
	SphereData::Generate(1.0f, 36, 18, vertices, indices); // radius = 1.0f, sectorCount = 36, stackCount = 18
	Mesh sphereMesh(vertices, indices); 


	//  CubeData 
    //std::vector<Vertex> vertices = CubeData::GetVertices();
    //std::vector<GLuint> indices = CubeData::GetIndices();
	
    // initialize the Mesh object  
    //Mesh objectMesh(vertices, indices);




    //main render loop
        double lastTime = glfwGetTime();
        int frameCount = 0;

    while (!glfwWindowShouldClose(window)) {
        /*
        // compute FPS
            double currentTime = glfwGetTime();
            frameCount++;

			//update the window title every second
            if (currentTime - lastTime >= 1.0) {
                double fps = double(frameCount) / (currentTime - lastTime);
                double msPerFrame = 1000.0 / double(frameCount);

				// update the window title with FPS and ms per frame
                std::string title = "PhongShader Framework - FPS: " + std::to_string((int)fps) + " (" + std::to_string(msPerFrame) + " ms)";
                glfwSetWindowTitle(window, title.c_str());

                // Reset counters
                frameCount = 0;
                lastTime = currentTime;
            }
            */


		// clear the screen
        glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		shaderProgram.Activate();

		// define uniform variables
        shaderProgram.SetVec3("lightColor", glm::vec3(1.0f, 1.0f, 1.0f));
        shaderProgram.SetVec3("objectColor", glm::vec3(1.0f, 0.5f, 0.31f));
        shaderProgram.SetVec3("lightPos", glm::vec3(1.2f, 1.0f, 2.0f));

		//camera position
        shaderProgram.SetVec3("viewPos", camera.Position);



        //model matrix 
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::rotate(model, glm::radians(45.0f), glm::vec3(1.0f, 1.0f, 0.0f));
        shaderProgram.SetMat4("model", model);


        //camera matrix
        camera.Matrix(45.0f, 0.1f, 100.0f, shaderProgram, "camMatrix");


        
        //cube drawing
        //objectMesh.Draw(shaderProgram);
        
		//sphere drawing
		sphereMesh.Draw(shaderProgram);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // cleanup
    shaderProgram.Delete();
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}