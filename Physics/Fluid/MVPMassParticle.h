#pragma once

#include "CGLib/Math/Vector3d.h"
#include "CGLib/Util/UnCopyable.h"

namespace Crystal {
	namespace Physics {
		class MVPVolumeParticle;

class MVPMassParticle : private UnCopyable
{
public:
	MVPMassParticle(MVPVolumeParticle* parent, const Math::Vector3df& point, const float mass);

	Math::Vector3df getPosition() const;

	Math::Vector3df getVelocity() const;

	MVPVolumeParticle* getParent() { return parent; }

	void setParent(MVPVolumeParticle* p) { this->parent = p; }

	void updatePosition(const Math::Vector3df& centerPosition);

	void updateVelocity(const Math::Vector3df& centerVelocity);

	float getMass() const { return mass; }

	void setPressureCoe(const float c) { this->pressureCoe = c; }

	float getPressureCoe() const { return this->pressureCoe; }

	void setViscosityCoe(const float v) { this->viscosityCoe = v; }

	float getViscosityCoe() const { return viscosityCoe; }

	Math::Vector3df position;

private:
	MVPVolumeParticle* parent;
	Math::Vector3df vector;
	Math::Vector3df velocity;
	float mass;
	float pressureCoe;
	float viscosityCoe;
};

	}
}