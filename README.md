# Phong Shader Framework 

A simple 3D graphics framework built from scratch with C++ and OpenGL. I made this without using game engines like Unity to truly understand how 3D rendering and math work behind the scenes.

## Main Features

*   **Camera System:** Moving around in a 3D world using View and Projection matrices.
*   **MVP Matrices (Model-View-Projection):** Using math to turn basic points into a real 3D object on the screen.
*   **Phong Lighting:** Making objects look real with 3 types of light:
    *   **Ambient:** The base light so shadows aren't completely black.
    *   **Diffuse:** The direct light hitting the object.
    *   **Specular:** The shiny spot reflecting into your eyes.

## Dependencies

You need these libraries to run the code:
*   **GLFW:** Creates the window and handles the keyboard/mouse.
*   **GLAD:** Connects our C++ code to OpenGL functions.
*   **GLM:** Does the heavy math (vectors and matrices).

## Project Structure

*   "Main.cpp": The main loop that runs the program and draws objects.
*   **Shader Module:** Loads shader files and sends data from the CPU to the GPU.
*   **Camera Module:** Acts as your eyes to look around the 3D world.
*   **GPU Memory (VAO, VBO, EBO):** Packages and sends 3D points to the GPU efficiently without wasting memory.
*   **Shaders (GLSL):**
    *   "default.vert": Puts the object into the correct position in 3D space.
    *   "default.frag": Colors every pixel and calculates the lighting.

## Documentation
[MVP](https://jsantell.com/model-view-projection/).\
[FOV](https://en.wikipedia.org/wiki/Field_of_view).\
[Phong lighting](https://learnopengl.com/Lighting/Basic-Lighting).