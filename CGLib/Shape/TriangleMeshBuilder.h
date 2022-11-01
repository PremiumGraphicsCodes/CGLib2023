#pragma once

#include "TriangleMesh.h"
#include "../Util/UnCopyable.h"
#include <memory>

namespace Crystal {
	namespace Math {
		template<typename T>
		class ISurface3d;
		template<typename T>
		class IVolume3d;
	}
	namespace Shape {

class TriangleMeshBuilder : private UnCopyable
{
public:
	TriangleMeshBuilder();

	void add(const Math::ISurface3d<float>& sphere, const int unum, const int vnum);

	void add(const Math::IVolume3d<float>& volume, const int unum, const int vnum, const int wnum);

	std::unique_ptr<TriangleMesh> build();

private:
	std::vector<TriangleFace> faces;
};

	}
}