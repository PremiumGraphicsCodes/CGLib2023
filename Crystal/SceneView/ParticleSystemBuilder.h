#pragma once

#include <vector>
#include <memory>

#include "../Math/Vector3d.h"

#include "ParticleSystem.h"

namespace Crystal {
	namespace Math {
		template<typename T>
		class ICurve3d;
		template<typename T>
		class ISurface3d;
		template<typename T>
		class IVolume3d;
	}
	namespace Shape {

class ParticleSystemBuilder
{
public:
	void add(const Math::ICurve3d<float>& curve, int unum);

	void add(const Math::ISurface3d<float>& surface, const int unum, const int vnum);

	void add(const Math::IVolume3d<float>& volume, const int unum, const int vnun, const int wnum);

	std::unique_ptr<ParticleSystem> toParticleSystem();

private:
	std::vector<Math::Vector3df> positions;
};

	}
}