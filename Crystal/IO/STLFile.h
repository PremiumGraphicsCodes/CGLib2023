#pragma once

#include <string>
#include <vector>

#include "CGLib/Math/Triangle3d.h"

namespace Crystal {
	namespace IO {

struct STLFace
{
	STLFace()
	{};

	explicit STLFace(const Math::Triangle3df& triangle) :
		STLFace(triangle, triangle.getNormal())
	{}

	STLFace(const Math::Triangle3df& triangle, const Math::Vector3df& normal) :
		triangle(triangle),
		normal(normal)
	{}

	Math::Triangle3df triangle;
	Math::Vector3df normal;
};

struct STLFile
{
	std::string header;
	size_t faceCount = 0;
	std::vector<STLFace> faces;
};

	}
}