#include "Shader.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <glm/glm/gtc/type_ptr.hpp>
#include <glm/glm/glm.hpp>

//read shader code from file
std::string get_file_contents(const char* filename)
{
	//binary file
    std::ifstream in(filename, std::ios::binary);

    if (in)
    {
        std::string contents;

		//provide the memory that fit the file size
        in.seekg(0, std::ios::end);
        contents.resize(in.tellg());

        //read the file 
        in.seekg(0, std::ios::beg);
        in.read(&contents[0], contents.size());
        in.close();
        return contents;
    }

    std::cout << "Damn it!!!, failed to open shader file: " << filename << std::endl;
    throw(errno);
}



// attach, compile and link shaders
Shader::Shader(const char* vertexFile, const char* fragmentFile)
{
	//read code from files
    std::string vertexCode = get_file_contents(vertexFile);
    std::string fragmentCode = get_file_contents(fragmentFile);

    const char* vertexSource = vertexCode.c_str();
    const char* fragmentSource = fragmentCode.c_str();

	//creat and compile shaders
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexSource, NULL);
    glCompileShader(vertexShader);

	//create and compile fragment shader
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
    glCompileShader(fragmentShader);

	//create and link shader program
    ID = glCreateProgram();
    glAttachShader(ID, vertexShader);
    glAttachShader(ID, fragmentShader);
    glLinkProgram(ID);

	//clean up
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}


//
void Shader::Activate()
{
    glUseProgram(ID);
}

void Shader::Delete()
{
    glDeleteProgram(ID);
}



//bool = int 
void Shader::SetBool(const std::string& name, bool value) const
{
    glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
}
void Shader::SetInt(const std::string& name, int value) const
{
    glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}


//
void Shader::SetFloat(const std::string& name, float value) const
{
    glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
}



//
void Shader::SetVec3(const std::string& name, const glm::vec3& value) const
{
    glUniform3fv(glGetUniformLocation(ID, name.c_str()), 1, glm::value_ptr(value));
}

void Shader::SetMat4(const std::string& name, const glm::mat4& matrix) const
{
    glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, glm::value_ptr(matrix));
}