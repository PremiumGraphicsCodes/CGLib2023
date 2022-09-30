#pragma once

#include "../Util/UnCopyable.h"
#include "../Math/Box3d.h"

namespace Crystal {
	namespace Shape {

class IShape : private UnCopyable
{
public:
	virtual Math::Box3df getBoundingBox() const = 0;

	//virtual ~IShape() {};
};
	}
}