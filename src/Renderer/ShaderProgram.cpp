#include "ShaderProgram.h"

#include <iostream>

Renderer::ShaderProgram::ShaderProgram(const std::string& vertexShader, const std::string& fragmentShader)
{
    GLuint vertexShaderID;
	if(CreateShader(vertexShader, GL_VERTEX_SHADER, vertexShaderID) == false)
	{
        std::cerr << "VERTEX SHADER COMPILE ERROR" << std::endl;
        return;
	}

    GLuint fragmentShaderID;
    if (CreateShader(fragmentShader, GL_FRAGMENT_SHADER, fragmentShaderID) == false)
    {
        std::cerr << "FRAGMENT SHADER COMPILE ERROR" << std::endl;
        glDeleteShader(vertexShaderID);
        return;
    }

    _ID = glCreateProgram();
    glAttachShader(_ID, vertexShaderID);
    glAttachShader(_ID, fragmentShaderID);
    glLinkProgram(_ID);

    GLint success;
    glGetProgramiv(_ID, GL_LINK_STATUS, &success);
    if(success == false)
    {
        GLchar infoLog[1024];
        glGetShaderInfoLog(_ID, sizeof(infoLog), nullptr, infoLog);
        std::cerr << "ERROR: LINK COMPILE ERROR: " << infoLog << std::endl;
    }
    else
    {
        _isCompiled = true;
    }

    glDeleteShader(vertexShaderID);
    glDeleteShader(fragmentShaderID);
}

Renderer::ShaderProgram::~ShaderProgram()
{
    glDeleteProgram(_ID);
}

bool Renderer::ShaderProgram::isCompiled() const
{
    return _isCompiled;
}

void Renderer::ShaderProgram::Use() const
{
    glUseProgram(_ID);
}

bool Renderer::ShaderProgram::CreateShader(const std::string& shader, const GLenum shaderType, GLuint& shaderID)
{
    shaderID = glCreateShader(shaderType);
    const char* sourceCode = shader.c_str();
    glShaderSource(shaderID, 1, &sourceCode, nullptr);
    glCompileShader(shaderID);

    GLint success;
    glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);
    if(success == false)
    {
        GLchar infoLog[1024];
        glGetShaderInfoLog(shaderID, sizeof(infoLog), nullptr, infoLog);
        std::cerr << "ERROR: SHADER COMPILE ERROR: " << infoLog << std::endl;
        return false;
    }
    return true;
}

Renderer::ShaderProgram& Renderer::ShaderProgram::operator=(ShaderProgram&& shaderProgram) noexcept
{
    glDeleteProgram(_ID);
    _ID = shaderProgram._ID;
    _isCompiled = shaderProgram._isCompiled;

    shaderProgram._ID = 0;
    shaderProgram._isCompiled = false;
    return *this;
}

Renderer::ShaderProgram::ShaderProgram(ShaderProgram&& shaderProgram) noexcept
{
    _ID = shaderProgram._ID;
    _isCompiled = shaderProgram._isCompiled;

    shaderProgram._ID = 0;
    shaderProgram._isCompiled = false;
}