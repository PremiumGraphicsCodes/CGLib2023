#pragma once

#include "IGLObject.h"
#include "glew.h"
#include <string>

namespace Crystal {
	namespace Shader {

class ShaderUnit : public IGLObject
{
public:
	enum class Stage
	{
		VERTEX,
		FRAGMENT,
		GEOMETRY,
		COMPUTE,
		NONE,
	};

	explicit ShaderUnit(const Stage stage);

	~ShaderUnit();

	//void setSource(const std::string& source) { this->source = source; }

	void create() override;

	void remove() override;

	GLuint getHandle() const { return id; }

private:
	GLuint id;
	Stage stage;
};

	}
}