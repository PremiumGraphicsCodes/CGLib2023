#pragma once

#include "CGLib/Util/UnCopyable.h"
#include "CGLib/Math/Vector3d.h"
#include <list>
#include <array>
#include <vector>

namespace Crystal {
	namespace Space {

class SpaceHash : private UnCopyable
{
public:
	SpaceHash(const double divideLength, const int tableSize);

	void add(const Math::Vector3df& position);

	std::vector<int> findNeighborIndices(const Math::Vector3df& position);

	//bool isEmpty(const Math::Vector3df& pos) const;

private:
	std::vector<std::list<int>> table;

	std::vector<Math::Vector3df> positions;

	int toHash(const Math::Vector3df& pos) const;

	int toHash(const std::array<int, 3>& index) const;

	std::array<int, 3> toIndex(const Math::Vector3df& pos) const;

	const double divideLength;
};

	}
}