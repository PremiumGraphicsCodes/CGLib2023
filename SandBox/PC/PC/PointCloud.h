#pragma once

#include <vector>
#include <memory>
#include "Point.h"
#include "CGLib/Math/Box3d.h"
#include "CGLib/Util/UnCopyable.h"

namespace Crystal {
	namespace PC {

class PointCloud : private UnCopyable
{
public:
	void add(std::unique_ptr<IPoint>&& point);

	const std::vector<std::unique_ptr<IPoint>>& getPoints() { return points; }

	Math::Box3df getBoundingBox() const;

private:
	std::vector<std::unique_ptr<IPoint>> points;
};
	}
}