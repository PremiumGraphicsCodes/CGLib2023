#pragma once

#include "MVPMassParticle.h"

#include "CGLib/Util/UnCopyable.h"

#include <vector>
#include <list>

namespace Crystal {
	namespace Physics {
		class MVPFluid;

class MVPVolumeParticle : private UnCopyable
{
public:
	MVPVolumeParticle(const float radius, const Math::Vector3dd& position);

	~MVPVolumeParticle();

	void clearMasses() { this->massParticles.clear(); }

	void setPosition(const Math::Vector3df& p) { this->position = p; }

	//void setVelocity(const Math::Vector3df& v) { this->velocity = v; }

	void setPressureCoe(const float c);

	void setViscosityCoe(const float c);

	void reset(bool resetMicro);

	void addNeighbor(MVPVolumeParticle* neighbor) { this->neighbors.push_back(neighbor); }

	void addMassParticle(MVPMassParticle* massParticle) { this->massParticles.push_back(massParticle); }

	void calculateDensity();

	//void calculatePressure();

	void calculatePressureForce(const float relaxationCoe, const float dt);

	void calculateViscosityForce();

	void stepTime(const float dt);

	void setRadius(const float r) { this->radius = r; }

	float getRadius() const { return radius; }

	std::vector<MVPMassParticle*> getPoints() { return massParticles; }

	Math::Vector3df getPosition() const { return position; }

	Math::Vector3df getVelocity() const { return velocity; }

	void addForce(const Math::Vector3dd& force) { this->force += force; }

	float getDensity() const;

	void updateMassPositions();

	void updateMassVelocities();

	void updateInnerPoints();

	float getSelfMass() { return restMass; }

	void setVelocity(const Math::Vector3df& velocity) { this->velocity = velocity; }

	void setRestMass(const float m) { this->restMass = m; }

	Math::Vector3df getAveragedCenter() const { return averagedCenter; }

	const std::vector<MVPMassParticle*>& getMassParticles() const { return massParticles; }

	const std::vector<MVPVolumeParticle*>& getNeighbors() const { return neighbors; }

	void addDx(const Math::Vector3df& dx) { this->averagedCenter -= dx; }

private:
	float pressureCoe;
	float viscosityCoe;
	float radius;
	std::vector<MVPMassParticle*> massParticles;
	std::vector<MVPMassParticle*> innerPoints;
	std::vector<MVPVolumeParticle*> neighbors;
	Math::Vector3df force;
	Math::Vector3df position;
	Math::Vector3df predictedPosition;
	Math::Vector3df velocity;
	Math::Vector3df averagedCenter;
	float restMass;
	float density;
	float pressure;
};

	}
}