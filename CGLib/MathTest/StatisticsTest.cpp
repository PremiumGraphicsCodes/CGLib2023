#include "gtest/gtest.h"

#include "../Math/Statistics.h"

using namespace Crystal::Math;

TEST(StatisticsTest, TestGetAverage)
{
	Statistics<float> stat({ 5,8,9,7 });
	EXPECT_FLOAT_EQ(7.25, stat.getAverage());
}

TEST(StatisticsTest, TestGetVariance)
{
	Statistics<float> stat({ 5,8,9,7 });
	EXPECT_FLOAT_EQ(2.1875, stat.getVariance());
}

TEST(StatisticsTest, TestGetStandardDeviation)
{
	Statistics<float> stat({ 5,8,9,7 });
	EXPECT_FLOAT_EQ(std::sqrt(2.1875), stat.getStandardDeviation());
}