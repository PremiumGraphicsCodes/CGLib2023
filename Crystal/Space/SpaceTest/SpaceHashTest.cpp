#include "gtest/gtest.h"

#include "../Space/SpaceHash.h"

using namespace Crystal::Math;
using namespace Crystal::Space;

TEST(SpaceHashTest, TestGetNeighborIndices)
{
	SpaceHash spaceHash(1.0, 100);
	spaceHash.add(Vector3df(0, 0, 0));

	const auto actual = spaceHash.findNeighborIndices(Vector3df(0, 0, 0));
	EXPECT_EQ(1, actual.size());
}