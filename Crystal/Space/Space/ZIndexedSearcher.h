#pragma once

#include "CGLib/Math/Vector3d.h"

#include "CGLib/Util/UnCopyable.h"

#include "ZOrderCurve3d.h"

#include <vector>
#include <list>

namespace Crystal {
	namespace Space {

class ZIndexedParticle
{
public:
	ZIndexedParticle(const unsigned int zIndex, const Math::Vector3df& position) :
		zIndex(zIndex),
		position(position)
	{}

	bool operator<(const ZIndexedParticle& rhs) const {
		return this->zIndex < rhs.zIndex;
	}

	/*
	bool operator==(const ZIndexedParticle& rhs) {
		return this->zIndex == rhs.zIndex;
	}
	*/

	Math::Vector3df getPosition() { return position; }

	int index;

private:
	unsigned int zIndex;
	Math::Vector3df position;
};

class ZIndexedSearcher : private UnCopyable
{
public:
	explicit ZIndexedSearcher(const float searchRadius, const Math::Vector3df& minPosition);

	void add(const Math::Vector3df& position);

	void sort();

	std::list<int> findNeighbors(const Math::Vector3df& position);

	std::array<unsigned int, 3> toIndex(const Math::Vector3df& position) const;

private:
	float searchRadius;
	Math::Vector3df minPosition;
	std::vector<ZIndexedParticle> points;
	ZOrderCurve3d curve;
};

	}
}