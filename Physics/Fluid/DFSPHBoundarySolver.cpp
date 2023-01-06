#include "DFSPHBoundarySolver.h"

#include "DFSPHParticle.h"

using namespace Crystal::Math;
using namespace Crystal::Physics;

DFSPHBoundarySolver::DFSPHBoundarySolver(const float timeStep, const Box3df& boundary) :
	timeStep(timeStep),
	boundary(boundary)
{
}

void DFSPHBoundarySolver::solve(const std::vector<DFSPHParticle*>& particles) {
	for (int i = 0; i < static_cast<int>(particles.size()); ++i) {
		const auto force = getBoundaryForce(particles[i]->getPosition());
		particles[i]->force += (force * particles[i]->getMass());
	}
}

Vector3df DFSPHBoundarySolver::getBoundaryForce(const Vector3df& center)
{
	Math::Vector3df force(0, 0, 0);

	force += getForceX(center.x);
	force += getForceY(center.y);
	force += getForceZ(center.z);

	return force;
}

Vector3df DFSPHBoundarySolver::getForceX(const float x)
{
	float over = 0;
	const auto maxx = boundary.getMax().x;
	const auto minx = boundary.getMin().x;
	if (x > maxx) {
		over = x - maxx;
	}
	else if (x < minx) {
		over = x - minx;
	}

	const float force = getForce(over);
	return Vector3df(1, 0, 0) * force;
}

Vector3df DFSPHBoundarySolver::getForceY(const float y)
{
	float over = 0;
	const auto maxy = boundary.getMax().y;
	const auto miny = boundary.getMin().y;
	if (y > maxy) {
		over = y - maxy;
	}
	else if (y < miny) {
		over = y - miny;
	}
	const float force = getForce(over);
	return Vector3df(0, 1, 0) * force;
}

Vector3df DFSPHBoundarySolver::getForceZ(const float z)
{
	float over = 0;
	const auto maxz = boundary.getMax().z;
	const auto minz = boundary.getMin().z;
	if (z > maxz) {
		over = z - maxz;
	}
	else if (z < minz) {
		over = z - minz;
	}
	const float force = getForce(over);
	return Vector3df(0, 0, 1) * force;
}

float DFSPHBoundarySolver::getForce(const float over)
{
	return -over / timeStep / timeStep;
}