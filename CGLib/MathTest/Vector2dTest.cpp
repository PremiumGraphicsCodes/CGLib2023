#include "gtest/gtest.h"

#include "../Math/Vector2d.h"

using namespace Crystal::Math;

TEST(Vector2dTest, TestGetLengthSquared)
{
	const Vector2df v(4, 3);

	const auto actual = getLengthSquared(v);
	EXPECT_FLOAT_EQ(25.0f, actual);
}

TEST(Vector2dTest, TestGetLength)
{
	const Vector2df v(4,3);

	const auto actual = getLength(v);
	EXPECT_FLOAT_EQ(5.0f, actual);
}

TEST(Vector2dTest, TestGetDistanceSquared)
{
	const Vector2df v1(1, 1);
	const Vector2df v2(5, 4);

	const auto actual = getDistanceSquared(v1, v2);
	EXPECT_FLOAT_EQ(25, actual);
}

TEST(Vector2dTest, TestGetDistance)
{
	const Vector2df v1(1,1);
	const Vector2df v2(5,4);

	const auto actual = getDistance(v1, v2);
	EXPECT_FLOAT_EQ(5.0f, actual);
}