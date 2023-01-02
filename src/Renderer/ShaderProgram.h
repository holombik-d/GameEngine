#pragma once
#include <glad/glad.h>
#include <string>

namespace Renderer
{
	class ShaderProgram
	{
	public:
		ShaderProgram(const std::string& vertexShader, const std::string& fragmentShader);
		~ShaderProgram();
		bool isCompiled() const;
		void Use() const;
		void SetInt(const std::string &name, GLint value);

		ShaderProgram() = delete;
		ShaderProgram(ShaderProgram&) = delete;
		ShaderProgram& operator=(const ShaderProgram&) = delete;

		ShaderProgram& operator=(ShaderProgram&& shaderProgram) noexcept;
		ShaderProgram(ShaderProgram&& shaderProgram) noexcept;

	private:
		bool CreateShader(const std::string& shader, const GLenum shaderType, GLuint& shaderID);
		bool _isCompiled = false;
		GLuint _ID = 0;
	};
}
