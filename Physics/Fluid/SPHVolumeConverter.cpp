#include "SPHVolumeConverter.h"

#include "CGLib/Math/Sphere3d.h"

#include "Crystal/Space/CompactSpaceHash.h"
#include "Crystal/Volume/SparseVolume.h"
#include "Crystal/Volume/SparseVolumeBuilder.h"

#include "WPCA.h"
#include "SPHKernel.h"

using namespace Crystal::Math;
using namespace Crystal::Space;
using namespace Crystal::Shape;
using namespace Crystal::Volume;
using namespace Crystal::Physics;

namespace {
	float getCubicSpline(const float distance, const float effectLength)
	{
		const auto q = distance * 2 / (effectLength);

		if (q < 1) {
			return (2.0f / 3.0f - q * q + 0.5f * q * q * q);
		}
		else if (q < 2) {
			return (std::pow(2.0f - q, 3.0f) / 6.0f);
		}
		else {
			return 0;
		}
	}
}

std::unique_ptr<SparseVolumef> SPHVolumeConverter::buildIsotoropic(const std::vector<Math::Vector3dd>& positions, const float particleRadius, const float cellLength)
{
	const auto searchRadius = particleRadius;
	if (positions.empty()) {
		return nullptr;
	}

	const SPHKernel kernel(searchRadius);

	for (const auto& p : positions) {
		particles.push_back(std::make_unique<SPHSurfaceParticle>(p, particleRadius));
	}
	calculateDensity(particleRadius);

	SparseVolumeBuilder builder;
	builder.build(Vector3df(cellLength), positions.size());
	for (auto& p : particles) {
		builder.add(Sphere3df(p->getPosition(), particleRadius));
	}
	auto volume = builder.get();
	const auto nodes = volume->getNodes();

	CompactSpaceHash spaceHash(particleRadius, (int)particles.size());
	for (const auto& p : particles) {
		spaceHash.add(p->getPosition());
	}

	std::vector<SparseVolumeNode<float>*> ns(nodes.begin(), nodes.end());
#pragma omp parallel for
	for (int i = 0; i < ns.size(); ++i) {
		auto node = ns[i];
		const auto nodePos = node->getPosition();
		const auto neighbors = spaceHash.findNeighborIndices(i);
		for (auto n : neighbors) {
			auto& sp = particles[n];
			const auto v = sp->getPosition() - nodePos;
			//const auto coe = 1400.0f / searchRadius / searchRadius / searchRadius;
			const auto w = /* coe * */ kernel.getCubicSpline(v) * sp->getMass() / sp->getDensity();
			const auto value = node->getValue();
			node->setValue(w + value);
		}
	}
	return std::move(volume);
}

std::unique_ptr<SparseVolumef> SPHVolumeConverter::buildAnisotoropic(const std::vector<Vector3dd>& positions, const float particleRadius, const float cellLength)
{
	if (positions.empty()) {
		return nullptr;
	}

	const auto searchRadius = particleRadius;
	const SPHKernel kernel(searchRadius);

	for (const auto& p : positions) {
		particles.push_back(std::make_unique<SPHSurfaceParticle>(p, particleRadius));
	}

	calculateAnisotropy(searchRadius);

	SparseVolumeBuilder builder;
	builder.build(Vector3df(cellLength), positions.size());
	for (auto& p : particles) {
		builder.add(Sphere3df(p->getPosition(), particleRadius));
	}
	auto volume = builder.get();
	const auto nodes = volume->getNodes();

	CompactSpaceHash spaceHash(searchRadius, (int)particles.size());

	for (const auto& p : particles) {
		spaceHash.add(p->getPosition());
	}

	std::vector<SparseVolumeNode<float>*> ns(nodes.begin(), nodes.end());
#pragma omp parallel for
	for (int i = 0; i < ns.size(); ++i) {
		auto node = ns[i];
		const auto nodePos = node->getPosition();
		const auto neighbors = spaceHash.findNeighborIndices(node->getPosition());
		for (auto n : neighbors) {
			auto& sp = particles[n];
			auto m = sp->getMatrix();
			//auto m = Matrix3df(0.5, 0, 0, 0, 0.5, 0, 0, 0, 0.5) / searchRadius;
			const auto v = Vector3df(sp->getPosition()) - nodePos;
			const Vector3df distance = m * v;
			//const auto d = glm::length(distance);
			const auto det = glm::determinant(m);
			const auto w = kernel.getCubicSpline(v) * det * sp->getMass() / sp->getDensity();
			node->setValue(node->getValue() + w);
		}
	}
	return std::move(volume);
}

std::unique_ptr<SparseVolumef> SPHVolumeConverter::createSparseVolume(const std::vector<Vector3dd>& particles, const float cellLength)
{
	Vector3dd resolution{ cellLength, cellLength, cellLength };
	auto sv = std::make_unique<SparseVolumef>(resolution, particles.size());
	return sv;
}

void SPHVolumeConverter::calculateDensity(const float searchRadius)
{
	const SPHKernel kernel(searchRadius);

	CompactSpaceHash spaceHash(searchRadius, particles.size());

	for (const auto& p : particles) {
		spaceHash.add(p->getPosition());
	}

#pragma omp parallel for
	for (int i = 0; i < particles.size(); ++i) {
		auto& p = particles[i];
		const auto indices = spaceHash.findNeighborIndices(p->getPosition());
		std::vector<Vector3df> neighbors;
		for (const auto& ix : indices) {
			neighbors.push_back(particles[ix]->getPosition());
		}
		p->calculateDensity(neighbors, searchRadius, kernel);
	}
}

void SPHVolumeConverter::calculateAnisotropy(const float searchRadius)
{
	const SPHKernel kernel(searchRadius);

	CompactSpaceHash spaceHash(searchRadius, particles.size());

	for (const auto& p : particles) {
		spaceHash.add(p->getPosition());
	}

#pragma omp parallel for
	for (int i = 0; i < particles.size(); ++i) {
		auto& p = particles[i];
		const auto indices = spaceHash.findNeighborIndices(p->getPosition());
		std::vector<Vector3df> neighbors;
		for (const auto& ix : indices) {
			neighbors.push_back(particles[ix]->getPosition());
		}

		p->calculateDensity(neighbors, searchRadius, kernel);
		WPCA wpca;
		wpca.setup(p->getPosition(), neighbors, searchRadius);
		const auto wm = wpca.calculateWeightedMean(p->getPosition(), neighbors, searchRadius);
		p->correctedPosition(0.95, wm);
		p->calculateAnisotoropicMatrix(neighbors, searchRadius);
	}
}