#include "CSPHFluid.h"

#include "CSPHParticle.h"

using namespace Crystal::Math;
using namespace Crystal::Physics;

CSPHFluid::CSPHFluid()
{

}

Box3df CSPHFluid::getBoundingBox() const
{
	auto bb = Box3df::createDegeneratedBox();
	for (auto p : particles) {
		bb.add(p->getPosition());
	}
	return bb;
}
