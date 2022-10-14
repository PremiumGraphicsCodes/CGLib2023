#pragma once

#include <vector>
#include <list>

#include "CGLib/Math/Vector3d.h"
#include "CGLib/Math/Box3d.h"

#include "MVPBoundarySolver.h"

namespace Crystal {
	namespace Physics {
		class MVPVolumeParticle;
		class MVPFluid;

		class MVPFluidSolver
		{
		public:
			MVPFluidSolver();

			explicit MVPFluidSolver(const int id);

			void setupBoundaries();

			void clear();

			void addFluidScene(MVPFluidScene* scene);

			void addBoundaryScene(MVPFluidScene* scene);

			void addEmitterScene(MVPFluidEmitterScene* scene);

			void addBoundary(CSGBoundaryScene* scene);

			void setMaxTimeStep(const float maxTimeStep) { this->maxTimeStep = maxTimeStep; }

			void setEffectLength(const float effectLength) { this->effectLength = effectLength; }

			void setExternalForce(const Math::Vector3df& externalForce) { this->externalForce = externalForce; }

			void setBuoyancy(const Math::Vector3df& buoyancy) { this->buoyancy = buoyancy; }

			void simulate();

			void step() override;

			int getTimeStep() const { return currentTimeStep; }

			std::list<MVPFluidScene*> getFluids() const { return fluids; }

			std::list<MVPFluidEmitterScene*> getEmitters() const { return emitters; }

			//std::vector<Math::Triangle3d> getTriangles() const { return triangles; }

		private:

			float calculateTimeStep(const std::vector<MVPVolumeParticle*>& particles);

			std::list<MVPFluid*> fluids;
			//std::list<MVPMassParticle*> tinyParticles;
			MVPBoundarySolver boundarySolver;
			float effectLength = 2.0f;
			float maxTimeStep = 0.03f;
			int currentTimeStep = 0;
			Math::Vector3df externalForce;
			Math::Vector3df buoyancy;
		};

	}
}