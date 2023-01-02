#include "ResourceManager.h"
#include "../Renderer/ShaderProgram.h"
#include <sstream>
#include <iostream>
#include <fstream>

#define STB_IMAGE_IMPLEMENTATION
#define STBI_ONLY_PNG
#include "stb_image.h"
#include "../Renderer/Texture2D.h"

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

std::shared_ptr<Renderer::Texture2D> ResourceManager::LoadTexture(const std::string& textureName, const std::string& texturePath)
{
	int channels = 0;
	int width = 0;
	int height = 0;

	stbi_set_flip_vertically_on_load(true);

	unsigned char* pixels = stbi_load(std::string(_path + "/" + texturePath).c_str(), &width, &height, &channels, 0);

	if(!pixels)
	{
		std::cerr << "Can`t load texture: " << texturePath << std::endl;
		return nullptr;
	}

	std::shared_ptr<Renderer::Texture2D> newTexture = _textures.emplace(textureName, std::make_shared<Renderer::Texture2D>(width, height, pixels, 
																		channels, GL_NEAREST, GL_CLAMP_TO_EDGE)).first->second;

	stbi_image_free(pixels);
	return newTexture;
}

std::shared_ptr<Renderer::Texture2D> ResourceManager::GetTexture(const std::string& textureName)
{
	TexturesMap::const_iterator iterator = _textures.find(textureName);
	if (iterator != _textures.end())
	{
		return iterator->second;
	}

	std::cerr << "Can`t find the texture: " << textureName;
	return nullptr;
}
