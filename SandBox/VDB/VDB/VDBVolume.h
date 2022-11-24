#pragma once

#include <memory>

#include "CGLib/Math/Box3d.h"
#include "CGLib/Util/UnCopyable.h"

namespace Crystal {
	namespace VDB {
		class VDBVolumeImpl;

class VDBVolume : private UnCopyable
{
public:
	VDBVolume();

	explicit VDBVolume(const float value);

	void setValue(const std::array<int, 3>& index, const float value);

	float getValue(const std::array<int, 3> index);

	void fill(const unsigned int coord1, const unsigned int coord2, const float value);

	int getActiveVoxelCount() const;

	//void transform(const Math::Matrix3df& m) override;

	//void transform(const Math::Matrix4df& m) override;

	Math::Box3df getBoundingBox() const;

	VDBVolumeImpl* getImpl() const { return impl.get(); }

	void setScale(const float scale);

private:
	std::unique_ptr<VDBVolumeImpl> impl;
};

	}
}