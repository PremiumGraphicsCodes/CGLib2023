#pragma once

#include "CGLib/Util/UnCopyable.h"
#include "CGLib/Math/Vector3d.h"
#include "CGLib/Math/Matrix3d.h"

#include "SPHKernel.h"
#include <vector>

namespace Crystal {
	namespace Physics {

class SPHSurfaceParticle : private UnCopyable
{
public:
	SPHSurfaceParticle(const Math::Vector3df& p, const float radius);

	Math::Vector3df getPosition() const { return position; }

	void correctedPosition(const float lamda, const Math::Vector3df& weightedMean);

	void calculateAnisotoropicMatrix(const std::vector<Math::Vector3df>& neighbors, const float searchRadius);

	void calculateDensity(const std::vector<Math::Vector3df>& neighbors, const float searchRadius, const SPHKernel& kernel);

	Math::Matrix3dd getMatrix() const { return matrix; }

	float getDensity() const { return density; }

	float getMass() const;

private:
	Math::Vector3df position;
	Math::Matrix3dd matrix;
	float density;
	float radius;
};

	}
}