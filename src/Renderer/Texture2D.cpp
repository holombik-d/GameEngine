#pragma once

#include "Texture2D.h"

namespace Renderer
{
	Texture2D::Texture2D(const GLuint width, const GLuint height, const unsigned char* data, const unsigned channels,
		const GLenum filter, const GLenum wrapMode) : _width(width), _height(height)
	{
		switch (channels)
		{
		case 4:
			_mode = GL_RGBA;
		case 3:
			_mode = GL_RGB;
		default:
			_mode = GL_RGBA;
			break;
		}

		glGenTextures(1, &_id);
		glBindTexture(GL_TEXTURE_2D, _id);
		glTexImage2D(GL_TEXTURE_2D, 0, _mode, _width, _height, 0, _mode, GL_UNSIGNED_BYTE, data);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapMode);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapMode);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filter);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filter);
		glGenerateMipmap(GL_TEXTURE_2D);

		glBindTexture(GL_TEXTURE_2D, 0);
	}

	Texture2D& Texture2D::operator=(Texture2D&& texture2d)
	{
		glDeleteTextures(1, &_id);
		_id = texture2d._id;
		texture2d._id = 0;

		_mode = texture2d._mode;
		texture2d._mode = 0;

		_width = texture2d._width;
		_height = texture2d._height;

		return *this;
	}

	Texture2D::Texture2D(Texture2D&& texture2d)
	{
		_id = texture2d._id;
		texture2d._id = 0;

		_mode = texture2d._mode;
		texture2d._mode = 0;

		_width = texture2d._width;
		_height = texture2d._height;
	}

	Texture2D::~Texture2D()
	{
		glDeleteTextures(1, &_id);
	}

	void Texture2D::Bind() const
	{
		glBindTexture(GL_TEXTURE_2D, _id);
	}
}
