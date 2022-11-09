#include "pch.h"

#include "../PC/GaussianFunc.h"

using namespace Crystal::PC;

TEST(GaussianFuncTest, TestGet) {
	GaussianFunc g(1.0f, 0.0f, 1.0f);
	const auto w = g.getWeight(0.0);
	EXPECT_NEAR(1, w, 1.0e-12);
  //EXPECT_TRUE(true);
}