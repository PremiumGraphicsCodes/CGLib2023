#include "IndexedSortBasedSeacher.h"
#include "IndexedParticle.h"

#include <algorithm>

using namespace Crystal::Math;
using namespace Crystal::Space;

void IndexedSortBasedSearcher::add(const Vector3df& position)
{
	IndexedParticle ip(position);
	ip.setGridId(effectLength);
	ip.setId(static_cast<int>(iparticles.size()));
	iparticles.push_back(ip);
}

void IndexedSortBasedSearcher::search()
{
	std::sort(iparticles.begin(), iparticles.end());
	// optimization for quad core.
	const int threads = 8;

	std::vector<std::vector<ParticlePair>> eachPairs(threads);

	std::vector<std::vector<IndexedParticle>::const_iterator> iters;
	for (int i = 0; i < threads; ++i) {
		iters.push_back(iparticles.begin() + i * iparticles.size() / threads);
	}
	iters.push_back(iparticles.end());

#pragma omp parallel for
	for (int i = 0; i < threads; ++i) {
		eachPairs[i] = search1(iparticles, iters[i], iters[i + 1], effectLength * effectLength);

	}

	for (size_t i = 0; i < eachPairs.size(); ++i) {
		pairs.insert(pairs.end(), eachPairs[i].begin(), eachPairs[i].end());
	}

#pragma omp parallel for
	for (int i = 0; i < threads; ++i) {
		eachPairs[i] = search2(iparticles, iters[i], iters[i + 1], effectLength * effectLength);
	}

	for (size_t i = 0; i < eachPairs.size(); ++i) {
		pairs.insert(pairs.end(), eachPairs[i].begin(), eachPairs[i].end());
	}
}

std::vector<ParticlePair> IndexedSortBasedSearcher::search1(const std::vector<IndexedParticle>& particles, std::vector<IndexedParticle>::const_iterator startIter, std::vector<IndexedParticle>::const_iterator endIter, const float effectLengthSquared)
{
	std::vector<ParticlePair> pairs;
	for (auto xIter = startIter; xIter != endIter; ++xIter) {
		const auto gridID = xIter->getGridId();
		const auto& centerX = xIter->getPosition();
		auto yIter = xIter;
		++yIter;// ignore itself.
		while (yIter != particles.end() && (yIter->getGridId() <= gridID + 1)) {
			const auto& centerY = yIter->getPosition();
			if (getDistanceSquared(centerX, centerY) < effectLengthSquared) {
				/*
				if (xIter->getParticle()->isBoundary() && yIter->getParticle()->isBoundary()) {
				++yIter;
				continue;
				}
				*/
				pairs.push_back(ParticlePair(xIter->getId(), yIter->getId()));
				//pairs.push_back(SPHParticlePair((*yIter), (*xIter)));
			}
			++yIter;
		}
	}
	return pairs;
}

std::vector<ParticlePair> IndexedSortBasedSearcher::search2(const std::vector<IndexedParticle>& particles, std::vector<IndexedParticle>::const_iterator startIter, std::vector<IndexedParticle>::const_iterator endIter, const float effectLengthSquared)
{
	std::vector<ParticlePair> pairs;

	std::vector<std::vector<IndexedParticle>::const_iterator> yIter(4, startIter);
	std::vector<int> offsetIds;
	offsetIds.push_back(1023);
	offsetIds.push_back(1047551);
	offsetIds.push_back(1048575);
	offsetIds.push_back(1049599);

	for (auto xIter = startIter; xIter != endIter; ++xIter) {
		for (size_t i = 0; i < 4; ++i) {
			const auto baseID = xIter->getGridId() + offsetIds[i];
			while (yIter[i] != particles.end() && (yIter[i]->getGridId() < baseID)) {
				++yIter[i];
			}

			const auto& centerX = xIter->getPosition();
			auto zIter = yIter[i];
			while (zIter != particles.end() && zIter->getGridId() <= baseID + 2) {
				const auto& centerZ = zIter->getPosition();
				if (getDistanceSquared(centerX, centerZ) < effectLengthSquared) {
					/*
					if (xIter->getParticle()->isBoundary() && zIter->getParticle()->isBoundary()) {
					++zIter;
					continue;
					}
					*/
					pairs.push_back(ParticlePair(xIter->getId(), zIter->getId()));
					//pairs.push_back(SPHParticlePair((*zIter), (*xIter)));
				}
				++zIter;
			}
		}
	}

	return pairs;
}