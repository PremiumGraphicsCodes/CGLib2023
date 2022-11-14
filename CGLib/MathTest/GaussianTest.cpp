#include "gtest/gtest.h"

#include "../Math/Gaussian.h"

using namespace Crystal::Math;

TEST(GaussianTest, TestGet)
{
	Gaussian g(1.0f, 0.0f, 1.0f);
	const auto w = g.getWeight(0.0);
	EXPECT_NEAR(1, w, 1.0e-12);
  //EXPECT_TRUE(true);
}

TEST(GaussianTest, TestCreateNormalDistributionFunc)
{
	const auto g = Gaussian::createNormalDistributionFunc(0.0, 1.0);
	const auto w = g.getWeight(0.0);
	EXPECT_NEAR(0.3984, w, 1.0e-3);
	//EXPECT_TRUE(true);
}