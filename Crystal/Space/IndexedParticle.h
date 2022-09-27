#pragma once

#include "CGLib/Math/Vector3d.h"
#include <array>

namespace Crystal {
	namespace Space {

class IndexedParticle
{
public:
	IndexedParticle() :
		position(0,0,0),
		gridId(0)
	{}

	explicit IndexedParticle(const Math::Vector3df& position) :
		position(position),
		gridId(0)
	{
	}

public:
	void setGridId(const float effectLength);

	Math::Vector3df getPosition() const { return position; }

	static int toGridId(const Math::Vector3df pos, const float effectLength);

	static std::array<int, 3> toIndex(const Math::Vector3df pos, const float effectLength);

	int getGridId() const { return gridId; }

	bool operator<(const IndexedParticle& rhs) {
		return this->getGridId() < rhs.getGridId();
	}

private:
	static int toIdX(std::array<int, 3> index);

private:
	Math::Vector3df position;
	int gridId;
};

	}
}