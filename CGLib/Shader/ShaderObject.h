#pragma once

#include "../Util/UnCopyable.h"

#include <vector>
#include <map>
#include <string>

#include "../Math/Vector3d.h"
#include "../Math/Matrix3d.h"
#include "../Math/Matrix4d.h"
#include "glew.h"

//#include "ShaderUnit.h"
#include "IGLObject.h"
#include "VertexAttribute.h"
#include "Uniform.h"

namespace Crystal {
	namespace Shader {
		class VertexBufferObject;
		class ShaderUnit;

class ShaderObject : public IGLObject
{
private:

public:
	ShaderObject(void);

	~ShaderObject(void);

	void create() override;

	void remove() override;

	GLuint findUniformLocation(const std::string& str);

	GLuint findAttribLocation(const std::string& str);

	GLuint getHandle() const { return handle; }

	void bind() const override;

	void unbind() const override;

	void enable(GLenum e);

	void disable(GLenum e);

	void drawPoints(const int count);

	void drawLines(const std::vector<unsigned int>& indices);

	void drawLines(const int count);

	void drawTriangles(const int count);

	void drawTriangles(const std::vector<unsigned int>& indices);

	void drawQuads(const int count);

	void bindOutput(const std::string& name);

	void bindOutput(const std::string& name, unsigned int number);

	void setLineWidth(const float width);

private:
	GLuint handle;
};


	}
}