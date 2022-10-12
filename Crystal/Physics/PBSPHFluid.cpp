#include "PBSPHFluid.h"

#include "PBSPHParticle.h"

using namespace Crystal::Math;
using namespace Crystal::Physics;

PBSPHFluid::PBSPHFluid() :
	kernel(1.0f),
	restDensity(1.0f),
	stiffness(0.05f),
	viscosity(0.1f),
	_isBoundary(false)
{
}

PBSPHFluid::~PBSPHFluid()
{
}

Box3df PBSPHFluid::getBoundingBox() const
{
	Box3df bb = Box3df::createDegeneratedBox();
	for (auto p : particles) {
		bb.add(p->getPosition());
	}
	return bb;
}

void PBSPHFluid::setEffectLength(const float effectLength)
{
	this->kernel = SPHKernel(effectLength);
}

void PBSPHFluid::setRestDensity(const float restDensity)
{
	this->restDensity = restDensity;
}