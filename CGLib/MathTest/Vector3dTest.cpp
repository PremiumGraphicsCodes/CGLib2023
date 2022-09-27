#include "gtest/gtest.h"

#include "../Math/Vector3d.h"

using namespace Crystal::Math;

TEST(Vector3dTest, TestGetLengthSquared)
{
	const Vector3df v(1, 2, 3);

	const auto actual = getLengthSquared(v);
	EXPECT_FLOAT_EQ(14, actual);
}

TEST(Vector3dTest, TestGetLength)
{
	const Vector3df v(1, 2, 3);

	const auto actual = getLength(v);
	EXPECT_FLOAT_EQ(std::sqrt(14.0f), actual);
}

TEST(Vector3dTest, TestGetDistanceSquared)
{
	const Vector3df v1(0, 0, 0);
	const Vector3df v2(1, 2, 3);

	const auto actual = getDistanceSquared(v1, v2);
	EXPECT_FLOAT_EQ(14, actual);
}

TEST(Vector3dTest, TestGetDistance)
{
	const Vector3df v1(0, 0, 0);
	const Vector3df v2(1, 2, 3);

	const auto actual = getDistance(v1, v2);
	EXPECT_FLOAT_EQ(std::sqrt(14.0f), actual);
}