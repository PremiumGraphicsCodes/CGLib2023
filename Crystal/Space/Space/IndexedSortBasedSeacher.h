#pragma once

#include "CGLib/Util/UnCopyable.h"

#include "IndexedParticle.h"
#include <vector>
//#include "ParticlePair.h"

namespace Crystal {
	namespace Space {

using ParticlePair = std::pair<int, int>;

class IndexedSortBasedSearcher : private UnCopyable
{
public:
	explicit IndexedSortBasedSearcher(const float effectLength) :
		effectLength(effectLength)
	{}

	void add(const Math::Vector3df& position);

	void search();

	std::vector<ParticlePair> getPairs() const { return pairs; }

	//std::list<SPHParticle*> find(const Math::Vector3d<float>& position);

private:
	std::vector<ParticlePair> pairs;

	std::vector<ParticlePair> search1(const std::vector<IndexedParticle>& particles, std::vector<IndexedParticle>::const_iterator startIter, std::vector<IndexedParticle>::const_iterator endIter, const float effectLengthSquared);

	std::vector<ParticlePair> search2(const std::vector<IndexedParticle>& particles, std::vector<IndexedParticle>::const_iterator startIter, std::vector<IndexedParticle>::const_iterator endIter, const float effectLengthSquared);

	std::vector<IndexedParticle> iparticles;
	const float effectLength;
};

	}
}