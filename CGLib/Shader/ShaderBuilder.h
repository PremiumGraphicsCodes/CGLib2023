#pragma once

#include "IGLObject.h"
#include "glew.h"

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

/*
class ShaderBuilder
{
public:
	void build();

private:
	void compile();

	void link();

};
*/
	}
}