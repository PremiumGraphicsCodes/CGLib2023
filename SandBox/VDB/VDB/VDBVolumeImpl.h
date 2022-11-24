#pragma once

#include "openvdb/openvdb.h"

#include "CGLib/Math/Vector3d.h"
#include "CGLib/Math/Matrix4d.h"

namespace Crystal {
	namespace VDB {

class VDBVolumeImpl
{
public:
	VDBVolumeImpl()
	{
	}

	explicit VDBVolumeImpl(openvdb::FloatGrid::Ptr ptr) :
		ptr(ptr)
	{}

	~VDBVolumeImpl();

	openvdb::FloatGrid::Ptr getPtr() { return ptr; }

	void setPtr(openvdb::FloatGrid::Ptr ptr) { this->ptr = ptr; }

	void setScale(const double scale);

	void setScale(const double sx, const double sy, const double sz);

	void setTransformMatrix(const Math::Matrix4df& matrix);

	void setTranslate(const Math::Vector3df& v);

private:
	openvdb::FloatGrid::Ptr ptr;
};

	}
}