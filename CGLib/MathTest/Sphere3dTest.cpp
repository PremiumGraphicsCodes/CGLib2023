#include "gtest/gtest.h"

#include "../Math/Sphere3d.h"

using namespace Crystal::Math;

namespace {
	const float tolerance = 1.0e-12f;
}

TEST(Sphere3dTest, TestGetPosition)
{
	const Sphere3df s(Vector3df(0.0, 0.0, 0.0), 1.0);

	EXPECT_TRUE(areSame(Vector3df( 0, 0, 1), s.getPosition(0.0, 0.0, 1.0), tolerance));
	EXPECT_TRUE(areSame(Vector3df( 0, 0, 1), s.getPosition(0.0, 0.5, 1.0), tolerance));
	EXPECT_TRUE(areSame(Vector3df( 0, 0, 1), s.getPosition(0.0, 1.0, 1.0), tolerance));

	EXPECT_TRUE(areSame(Vector3df( 0, 0, 1), s.getPosition(0.0, 0.5, 1.0), tolerance));
	EXPECT_TRUE(areSame(Vector3df(-1, 0, 0), s.getPosition(0.5, 0.5, 1.0), tolerance));
	EXPECT_TRUE(areSame(Vector3df( 0, 0,-1), s.getPosition(1.0, 0.5, 1.0), tolerance));

	EXPECT_TRUE(areSame(Vector3df( 0, 0,-1), s.getPosition(1.0, 0.0, 1.0), tolerance));
	EXPECT_TRUE(areSame(Vector3df( 0, 0,-1), s.getPosition(1.0, 0.5, 1.0), tolerance));
	EXPECT_TRUE(areSame(Vector3df( 0, 0,-1), s.getPosition(1.0, 1.0, 1.0), tolerance));
}

TEST(Sphere3dTest, TestGetNormal)
{
	const Sphere3df s(Vector3df(0.0, 0.0, 0.0), 1.0);

	EXPECT_TRUE(areSame(Vector3df( 0, 0, 1), s.getNormal(0.0, 0.0), tolerance));
	EXPECT_TRUE(areSame(Vector3df( 1, 0, 0), s.getNormal(0.5, 0.0), tolerance));
	EXPECT_TRUE(areSame(Vector3df( 0, 0,-1), s.getNormal(1.0, 0.0), tolerance));
}