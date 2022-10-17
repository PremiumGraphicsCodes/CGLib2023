#include "PBSPHBoundarySolver.h"

#include "PBSPHParticle.h"
#include "SPHKernel.h"

using namespace Crystal::Math;
using namespace Crystal::Physics;

namespace {
	SPHKernel kernel;
}

PBSPHBoundarySolver::PBSPHBoundarySolver(const Box3df& boundary) :
	boundary(boundary)
{
}

void PBSPHBoundarySolver::addDX(const std::vector<PBSPHParticle*>& particles, const float dt)
{
	for (int i = 0; i < static_cast<int>(particles.size()); ++i) {
		const auto over = getOverVector(particles[i]->getPredictPosition());
		particles[i]->addDensity(glm::length(over), particles[i]->getMass());
		//particles[i]->calculatePressure(-over);
		//particles[i]->dx -= over * 0.1f;
		//particles[i]->addExternalForce(-over / dt / dt);
	}
}

void PBSPHBoundarySolver::calculatePressure(const std::vector<PBSPHParticle*>& particles)
{
	for (int i = 0; i < static_cast<int>(particles.size()); ++i) {
		const auto over = getOverVector(particles[i]->getPredictPosition());
		//particles[i]->calculatePressure(over);
		particles[i]->dx -= over * 0.1f;
		//particles[i]->addExternalForce(-over / dt / dt);
	}
}

void PBSPHBoundarySolver::calculateViscosity(const std::vector<PBSPHParticle*>& particles)
{
	/*
	for (int i = 0; i < static_cast<int>(particles.size()); ++i) {
		const auto over = getOverVector(particles[i]->getPredictPosition());
		//particles[i]->calculatePressure(over);
		const auto coe = glm::length(over) * 1.0f;
		particles[i]->xvisc = coe * -particles[i]->getVelocity();
		//particles[i]->addExternalForce(-over / dt / dt);
	}
	*/
}



bool PBSPHBoundarySolver::isBoundary(PBSPHParticle* particle)
{
	const auto& max = boundary.getMax();
	const auto& min = boundary.getMin();
	const auto& pos = particle->getPosition();
	const auto radii = particle->getEffectLength();
	if (pos.x + radii > max.x) {
		return true;
	}
	if (pos.y + radii > max.y) {
		return true;
	}
	if (pos.z + radii > max.z) {
		return true;
	}
	if (pos.x - radii < min.x) {
		return true;
	}
	if (pos.y - radii < min.y) {
		return true;
	}
	if (pos.z - radii < min.z) {
		return true;
	}
	return false;
}

/*
Vector3df PBSPHBoundarySolver::getBoundaryPosition(PBSPHParticle* particle)
{
	assert(isBoundary(particle));
	const auto& pos = particle->getPosition();
	const auto radii = particle->getEffectLength();
	if (pos.x + radii > boundary.getMaxX()) {
		return Vector3df(boundary.getMaxX() + radii, pos.y, pos.z);
	}
	if (pos.y + radii > boundary.getMaxY()) {
		return Vector3df(pos.x, boundary.getMaxY() + radii, pos.z);
	}
	if (pos.z + radii > boundary.getMaxZ()) {
		return Vector3df(pos.x, pos.y, boundary.getMaxZ() + radii);
	}
	if (pos.x - radii < boundary.getMinX()) {
		return Vector3df(boundary.getMinX() - radii, pos.y, pos.z);
	}
	if (pos.y - radii < boundary.getMinY()) {
		return Vector3df(pos.x, boundary.getMinY() - radii, pos.z);
	}
	if (pos.z - radii < boundary.getMinZ()) {
		return Vector3df(pos.x, pos.y, boundary.getMinZ() - radii);
	}
	assert(false);
	return Vector3df(0, 0, 0);
}
*/

Vector3df PBSPHBoundarySolver::getOverVector(const Vector3df& position)
{
	return Vector3df(getOverX(position.x), getOverY(position.y), getOverZ(position.z));
}

float PBSPHBoundarySolver::getOverX(const float x)
{
	const auto& max = boundary.getMax();
	const auto& min = boundary.getMin();

	float over = 0;
	if (x > max.x) {
		over = x - max.x;
	}
	else if (x < min.x) {
		over = x - min.x;
	}
	return over;
}

float PBSPHBoundarySolver::getOverY(const float y)
{
	const auto& max = boundary.getMax();
	const auto& min = boundary.getMin();

	float over = 0;
	if (y > max.y) {
		over = y - max.y;
	}
	else if (y < min.y) {
		over = y - min.y;
	}
	return over;
}

float PBSPHBoundarySolver::getOverZ(const float z)
{
	const auto& max = boundary.getMax();
	const auto& min = boundary.getMin();

	float over = 0;
	if (z > max.z) {
		over = z - max.z;
	}
	else if (z < min.z) {
		over = z - min.z;
	}
	return over;
}