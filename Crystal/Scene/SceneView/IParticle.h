#pragma once

#include "CGLib/Math/Vector3d.h"

namespace Crystal {
	namespace Shape {

class IParticle
{
public:
	virtual ~IParticle() = default;

	virtual Math::Vector3df getPosition() const = 0;
};

struct Particle : public IParticle
{
public:
	explicit Particle(const Math::Vector3df& p) {
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