#pragma once

#include "CGLib/Math/Box3d.h"

#include <array>
#include <vector>

namespace Crystal {
	namespace Volume {

template<typename T>
class Volume
{
public:
	Volume();

	Volume(const Math::Box3df& box, const std::array<size_t, 3>& resolutions);

	Math::Box3df getBoundingBox() const { return box; }

	std::array<size_t, 3> getResolutions() const { return resolutions; }

	Math::Vector3df getCellPosition(const size_t i, const size_t j, const size_t k) const;

	std::array<size_t, 3> getIndexFromPosition(const Math::Vector3df& position);

	Math::Vector3df getCellLength() const;

	T getValue(const size_t i, const size_t j, const size_t k) const { return nodes[i][j][k]; }

	void setValue(const size_t i, const size_t j, const size_t k, const T value) { nodes[i][j][k] = value; }

	//void fill(const T value) { this->nodes.fill(value); }

private:
	Math::Box3df box;
	std::array<size_t, 3> resolutions;
	std::vector<std::vector<std::vector<T>>> nodes;
};

using Volumef = Volume<float>;
using Volumed = Volume<double>;

	}
}