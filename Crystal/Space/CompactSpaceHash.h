#pragma once

#include "CGLib/Util/UnCopyable.h"
#include "CGLib/Math/Vector3d.h"
#include "ZOrderCurve3d.h"
#include <vector>
#include <list>
#include <functional>

namespace Crystal {
	namespace Space {

class CompactSpaceCell
{
public:
	unsigned int cellId;
	std::array<int, 3> index;
	std::vector<int> particleIndices;
};

class CompactSpaceHash : private UnCopyable
{
public:
	CompactSpaceHash();

	CompactSpaceHash(const double divideLength, const int tableSize);

	~CompactSpaceHash();

	void setup(const double divideLength, const int tableSize);

	void clear();

	void add(const Math::Vector3df& position);

	std::vector<int> findNeighborIndices(const int index);

	/*
	std::vector<int> findNeighbors(const Math::Vector3df& position);
	*/

	std::vector<int> find(const int index) const;

	std::vector<int> find(const std::array<int, 3>& position) const;

	std::array<int, 3> toIndex(const Math::Vector3df& pos) const;

	unsigned int toZIndex(const std::array<int, 3>& index) const;

	std::array<unsigned int, 3> fromZIndex(unsigned int index) const;

	Math::Vector3df toPosition(const std::array<int, 3>& index) const;

	bool isEmpty(const Math::Vector3df& pos) const;

	//std::vector<CompactSpaceCell*> getCells() const { return cells; }

private:
	std::vector<std::vector<CompactSpaceCell*>> table;
	std::vector<CompactSpaceCell*> cells;
	std::vector<Math::Vector3df> positions;

	unsigned int toHash(const Math::Vector3df& pos) const;

	unsigned int toHash(const std::array<int, 3>& index) const;

	//std::array<int, 3> fromZIndex(unsigned int index) const;

	double divideLength;

	ZOrderCurve3d zCurve;
};

	}
}