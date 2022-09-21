#include "gtest/gtest.h"

#include "../Math/Vector3d.h"

using namespace Crystal::Math;

TEST(Vector3dTest, TestGetDistanceSquared)
{
	Vector3df v1(0, 0, 0);
	Vector3df v2(1, 2, 3);

	const auto actual = getDistanceSquared(v1, v2);
	EXPECT_DOUBLE_EQ(14, actual);
}