#pragma once

#include <list>
#include <vector>
#include <memory>

#include "CGLib/Util/UnCopyable.h"
#include "CGLib/Math/Vector3d.h"

namespace Crystal {
	namespace Physics {
		class CSPHFluid;
		class SPHKernel;

class CSPHParticle : private UnCopyable
{
public:
	CSPHParticle(const Math::Vector3df& center, const float radius, CSPHFluid* fluid);

	virtual ~CSPHParticle() {};

	float getDensityRatio() const;

	float getPressure() const;

	float getMass() const;

	float getVolume() const;

	float getRestVolume() const;

	void addForce(const Math::Vector3df& force) { this->force += force; }

	void setForce(const Math::Vector3df& force) { this->force = force; }

	Math::Vector3df getForce() const { return force; }

	//void setDefaultDensity() { this->density = fluid->getDensity(); }

	float getDensity() const { return density; }

	void addDensity(const float density) { this->density += density; }

	void init();

	Math::Vector3df getAccelaration() { return force / density; }

	Math::Vector3df getVelocity() const { return velocity; }

	void setVelocity(const Math::Vector3df& velocity) { this->velocity = velocity; }

	void addVelocity(const Math::Vector3df& velocity) { this->velocity += velocity; }

	void forwardTime(const float timeStep);

	void addExternalForce(const Math::Vector3df& force);

	void solveNormal(const CSPHParticle& rhs);

	void solveSurfaceTension(const CSPHParticle& rhs);

	void solvePressureForce(const CSPHParticle& rhs);

	void solveViscosityForce(const CSPHParticle& rhs);

	void addSelfDensity();

	void addDensity(const CSPHParticle& rhs);

	Math::Vector3df getNormal() const { return normal; }

	//bool isBoundary() const { return fluid->isBoundary; }

	Math::Vector3df getPosition() const { return position; }

	float getDiameter() const { return radius * 2.0f; }

	void move(const Math::Vector3df& v);

	void setKernel(SPHKernel* kernel) { this->kernel = kernel; }

private:
	float density;
	float radius;
	Math::Vector3df position;
	Math::Vector3df force;
	Math::Vector3df velocity;
	Math::Vector3df normal;
	CSPHFluid* fluid;

protected:
	SPHKernel* kernel;
};

	}
}