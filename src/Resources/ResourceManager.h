#pragma once
#include <map>
#include <memory>
#include <string>
#include "../Renderer/ShaderProgram.h"
class ResourceManager //Todo move to singleton
{
public:
	ResourceManager(const std::string& executablePath);
	~ResourceManager() = default;

	ResourceManager(const ResourceManager&) = delete;
	ResourceManager& operator=(const ResourceManager&) = delete;
	ResourceManager& operator=(ResourceManager&&) = delete;
	ResourceManager(ResourceManager&&) = delete;

	std::shared_ptr<Renderer::ShaderProgram> LoadShader(const std::string& shaderName, const std::string& vertexPath, const std::string& fragmentPath);
	std::shared_ptr<Renderer::ShaderProgram> GetShader(const std::string& shaderName);

	void LoadTexture(const std::string& textureName, const std::string& texturePath);
private:
	std::string GetFileString(const std::string& relativeFilePath);

	typedef std::map<const std::string, std::shared_ptr<Renderer::ShaderProgram>> ShaderProgramsMap;
	ShaderProgramsMap _ShaderProgramsMap;

	std::string _path;
};
