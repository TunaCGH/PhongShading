#include "Mesh.h"


//constructor
Mesh::Mesh(
    const std::vector<Vertex>& vertices,
    const std::vector<GLuint>& indices)
{
    this->vertices = vertices;
    this->indices = indices;

    SetupMesh();
}

//setup the mesh
void Mesh::SetupMesh()
{
    vao.Bind();

    vbo = new VBO(
        (GLfloat*)vertices.data(),
        vertices.size() * sizeof(Vertex)
    );

    ebo = new EBO(
        indices.data(),
        indices.size() * sizeof(GLuint)
    );

    vao.LinkAttrib(
        *vbo,
        0,
        3,
        GL_FLOAT,
        sizeof(Vertex),
        (void*)offsetof(Vertex, Position)
    );

    vao.LinkAttrib(
        *vbo,
        1,
        3,
        GL_FLOAT,
        sizeof(Vertex),
        (void*)offsetof(Vertex, Normal)
    );

    vao.Unbind();
}

//draw the mesh
void Mesh::Draw(Shader& shader)
{
    shader.Activate();
    vao.Bind();

    glDrawElements(
        GL_TRIANGLES,
		static_cast<GLsizei>(indices.size()),// force to GLsizei
        GL_UNSIGNED_INT,
        0
    );

    vao.Unbind();
}


Mesh::~Mesh()
{
    if (vbo)
    {
        vbo->Delete();
        delete vbo;
    }

    if (ebo)
    {
        ebo->Delete();
        delete ebo;
    }

    vao.Delete();
}


