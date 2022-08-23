#pragma once

#include "IGLObject.h"
#include "glew.h"
#include "ShaderObject.h"
#include <string>
#include <memory>

namespace Crystal {
	namespace Shader {

class VertexShader : public IGLObject
{
public:
	VertexShader();

	~VertexShader();

	void create() override;

	void remove() override;

	GLuint getHandle() const { return id; }

private:
	GLuint id;
};

class FragmentShader : public IGLObject
{
public:
	FragmentShader();

	~FragmentShader();

	void create() override;

	void remove() override;

	GLuint getHandle() const { return id; }

private:
	GLuint id;
};

class GeometryShader : public IGLObject
{
public:
	GeometryShader();

	~GeometryShader();

	void create() override;

	void remove() override;

	GLuint getHandle() const { return id; }

private:
	GLuint id;
};

class ComputeShader : public IGLObject
{
public:
	ComputeShader();

	~ComputeShader();

	void create() override;

	void remove() override;

	GLuint getHandle() const { return id; }

private:
	GLuint id;
};

class ShaderBuilder
{
public:
	void build();

private:
	bool compile(const std::string& source, const GLuint id);

	bool link();

	std::unique_ptr<ShaderObject> shader;

	std::string vsSource;
	std::string fsSource;

	VertexShader vertexShader;
	FragmentShader fragmentShader;

	std::string log;
};

	}
}