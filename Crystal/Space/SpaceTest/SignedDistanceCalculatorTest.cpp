#include "gtest/gtest.h"
#include "../Space/SignedDistanceCalculator.h"

#include "CGLib/Math/Sphere3d.h"

using namespace Crystal::Math;
using namespace Crystal::Space;

TEST(SignedDistanceCalculatorTest, TestSphere)
{
	SignedDistanceCalculator<float> c;
	Sphere3df sphere(Vector3df(0, 0, 0), 10.0f);
	const auto d = c.calculate(Vector3df(11, 0, 0), sphere);
	EXPECT_FLOAT_EQ(d, 1.0f);

	const auto d2 = c.calculate(Vector3df(9, 0, 0), sphere);
	EXPECT_FLOAT_EQ(d2, -1.0f);

}