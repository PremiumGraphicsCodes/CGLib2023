#include "pch.h"

#include "../PC/NormalEstimator.h"

using namespace Crystal::Math;
using namespace Crystal::PC;

TEST(NormalEstimatorTest, TestEstimate)
{
	NormalEstimator estimator;
	estimator.add(Vector3df(0, 0, 0));
	estimator.add(Vector3df(1, 0, 0));
	estimator.add(Vector3df(0, 1, 0));
	estimator.estimate(2.0f);
	const auto normals = estimator.getNormals();

	EXPECT_FLOAT_EQ(normals[0].x, 0.0f);
	EXPECT_FLOAT_EQ(normals[0].y, 0.0f);
	EXPECT_FLOAT_EQ(normals[0].z, 1.0f);
	//EXPECT_TRUE(true);
}
