#pragma once

#include "CGLib/Math/Vector3d.h"

namespace Crystal {
	namespace PC {

class IPoint
{
public:
	virtual ~IPoint() = default;

	virtual Math::Vector3df getPosition() const = 0;
};

struct Point : public IPoint
{
public:
	explicit Point(const Math::Vector3df& p) {
		this->pos = p;
	}

	Math::Vector3df getPosition() const override {
		return pos;
	}

private:
	Math::Vector3df pos;
};


	}
}