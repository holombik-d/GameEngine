#include "ResourceManager.h"
#include "../Renderer/ShaderProgram.h"
#include <sstream>
#include <iostream>
#include <fstream>

ResourceManager::ResourceManager(const std::string& executablePath)
{
	std::size_t found = executablePath.find_last_of("/\\");
	_path = executablePath.substr(0, found);
}

std::shared_ptr<Renderer::ShaderProgram> ResourceManager::LoadShader(const std::string& shaderName,
	const std::string& vertexPath, const std::string& fragmentPath)
{
	std::string vertexString = GetFileString(vertexPath);
	if(vertexString.empty())
	{
		std::cerr << "No vertex shader" << std::endl;
		return nullptr;
	}

	std::string fragmentString = GetFileString(fragmentPath);
	if (fragmentString.empty())
	{
		std::cerr << "No fragment shader" << std::endl;
		return nullptr;
	}

	std::shared_ptr<Renderer::ShaderProgram>& newShader = _ShaderProgramsMap.emplace(shaderName, std::make_shared<Renderer::ShaderProgram>(vertexString, fragmentString)).first->second;
	if(newShader->isCompiled())
	{
		return newShader;
	}

	std::cerr << "Can`t load shader program: " << "Vertex: " << vertexPath << " " << "Fragment: " << fragmentPath;
	return nullptr;
}

std::shared_ptr<Renderer::ShaderProgram> ResourceManager::GetShader(const std::string& shaderName)
{
	ShaderProgramsMap::const_iterator iterator = _ShaderProgramsMap.find(shaderName);
	if(iterator != _ShaderProgramsMap.end())
	{
		return iterator->second;
	}

	std::cerr << "Can`t find shader program: " << shaderName;
	return nullptr;
}

std::string ResourceManager::GetFileString(const std::string& relativeFilePath)
{
	std::ifstream file;
	file.open(_path + "/" + relativeFilePath.c_str(), std::ios::in | std::ios::binary);

	if(file.is_open() == false)
	{
		std::cerr << "Failed to open: " << relativeFilePath << std::endl;
		return std::string{};
	}

	std::stringstream buffer;
	buffer << file.rdbuf();
	return buffer.str();
}
