#include "gtest/gtest.h"

#include "Crystal/Space/CompactSpaceHash.h"

using namespace Crystal::Math;
using namespace Crystal::Space;

TEST(CompactSpaceHashTest, TestGetNeighborIndices)
{
	CompactSpaceHash spaceHash(1.0, 100);
	spaceHash.add(Vector3df(0, 0, 0));
	spaceHash.add(Vector3df(0.5, 0, 0));

	const auto actual = spaceHash.findNeighborIndices(0);
	EXPECT_EQ(1, actual.size());
}