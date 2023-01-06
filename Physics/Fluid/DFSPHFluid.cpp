#include "DFSPHFluid.h"

#include "DFSPHParticle.h"

using namespace Crystal::Math;
using namespace Crystal::Physics;

DFSPHFluid::DFSPHFluid()
{

}

Box3df DFSPHFluid::getBoundingBox() const
{
	auto bb = Box3df::createDegeneratedBox();
	for (const auto& p : particles) {
		bb.add(p->getPosition());
	}
	return bb;
}

void DFSPHFluid::setEffectLength(const float effectLength)
{
	this->kernel = SPHKernel(effectLength);
}

