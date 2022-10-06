#include "CSPHBoundarySolver.h"

#include "CSPHParticle.h"

using namespace Crystal::Math;
using namespace Crystal::Physics;

CSPHBoundarySolver::CSPHBoundarySolver(const float timeStep, const Box3df& boundary) :
	timeStep(timeStep),
	boundary(boundary)
{
}

void CSPHBoundarySolver::solve(const std::vector<CSPHParticle*>& particles) {
#pragma omp parallel for
	for (int i = 0; i < static_cast<int>(particles.size()); ++i) {
		const auto force = getBoundaryForce(particles[i]->getPosition());
		particles[i]->addForce(force * particles[i]->getDensity());
	}
}

Vector3df CSPHBoundarySolver::getBoundaryForce(const Vector3df& center)
{
	Math::Vector3df force(0, 0, 0);

	force += getForceX(center.x);
	force += getForceY(center.y);
	force += getForceZ(center.z);

	return force;
}

Vector3df CSPHBoundarySolver::getForceX(const float x)
{
	const auto minX = this->boundary.getMin().x;
	const auto maxX = this->boundary.getMax().x;
	float over = 0;
	if (x > maxX) {
		over = x - maxX;
	}
	else if (x < minX) {
		over = x - minX;
	}

	const float force = getForce(over);
	return Vector3df(1, 0, 0) * force;
}

Vector3df CSPHBoundarySolver::getForceY(const float y)
{
	const auto minY = this->boundary.getMin().y;
	const auto maxY = this->boundary.getMax().y;
	float over = 0;
	if (y > maxY) {
		over = y - maxY;
	}
	else if (y < minY) {
		over = y - minY;
	}
	const float force = getForce(over);
	return Vector3df(0, 1, 0) * force;
}

Vector3df CSPHBoundarySolver::getForceZ(const float z)
{
	const auto minZ = this->boundary.getMin().z;
	const auto maxZ = this->boundary.getMax().z;
	float over = 0;
	if (z > maxZ) {
		over = z - maxZ;
	}
	else if (z < minZ) {
		over = z - minZ;
	}
	const float force = getForce(over);
	return Vector3df(0, 0, 1) * force;
}

float CSPHBoundarySolver::getForce(const float over)
{
	return -over / timeStep / timeStep;
}