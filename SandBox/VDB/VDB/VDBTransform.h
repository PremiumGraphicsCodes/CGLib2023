#pragma once

#include "VDBVolume.h"

namespace Crystal {
	namespace VDB {

class VDBTransform
{
public:
	enum class TransformType {
		Point,
		Box,
		Quad,
	};

	void transformGeometry();

private:
	VDBVolume* source = nullptr;
	VDBVolume* target = nullptr;
};

	}
}