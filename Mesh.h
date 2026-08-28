#pragma once

#include <vector>

#include "Vertex.h"
#include "VAO.h"
#include "VBO.h"
#include "EBO.h"
#include "Shader.h"

class Mesh
{
public:

    // Mesh data
    std::vector<Vertex> vertices;
    std::vector<GLuint> indices;

    // OpenGL objects
    VAO vao;
    VBO* vbo;
    EBO* ebo;

    // Constructor
    Mesh(
        const std::vector<Vertex>& vertices,
        const std::vector<GLuint>& indices
    );

    // Draw mesh
    void Draw(Shader& shader);

	// Destructor
    ~Mesh();

private:

    void SetupMesh();
};

