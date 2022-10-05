#include "gtest/gtest.h"
#include "../Space/IntersectionCalculator.h"

#include "CGLib/Math/Ray3d.h"
#include "CGLib/Math/Sphere3d.h"
#include "CGLib/Math/Plane3d.h"
#include "CGLib/Math/Triangle3d.h"

using namespace Crystal::Math;
using namespace Crystal::Space;

namespace {
	const float tolerance = 1.0e-9f;

	Triangle3df getTriangle()
	{
		return Triangle3df({ Vector3dd(0,0,0), Vector3dd(10, 0, 0), Vector3dd(0, 10, 0) });
	}
}

TEST(IntersectionCalculatorTest, TestRayAndSphere)
{
	IntersectionCalculator<float> c;
	Ray3df ray(Vector3df(0,0,0), Vector3df(1,0,0));
	Sphere3df sphere(Vector3df(10, 0, 0), 1.0f);
	const auto found = c.calculateIntersection(ray, sphere, tolerance);
	EXPECT_TRUE(found);
	const auto actual = c.getIntersections()[0];
	Vector3df expected(9, 0, 0);
	EXPECT_TRUE(areSame(expected, actual, tolerance));
}

TEST(IntersectionCalculatorTest, TestRayAndPlane)
{
	IntersectionCalculator<float> c;
	Ray3df ray(Vector3df(0, 0, 0), Vector3df(1, 0, 0));
	Plane3df plane(Vector3df(10, 0, 0), Vector3df(-1, 0, 0));
	const auto found = c.calculateIntersection(ray, plane, tolerance);
	EXPECT_TRUE(found);
	Vector3df expected(10, 0, 0);
	const auto actual = c.getIntersections()[0];
	EXPECT_TRUE(areSame(expected, actual, tolerance));
}

TEST(IntersectionCalculatorTest, TestRayAndTriangle)
{
	IntersectionCalculator<float> algo;
	const auto& triangle = getTriangle();

	{
		const Ray3df ray(Vector3df(1, 1, 1), Vector3df(0, 0, -1));
		EXPECT_TRUE(algo.calculateIntersection(ray, triangle, tolerance));
		const auto& intersections = algo.getIntersections();
		EXPECT_EQ(1, intersections.size());
		const auto& i = intersections[0];
		EXPECT_TRUE(areSame( Vector3df(1, 1, 0), i, tolerance));
	}

	/*
	{
		const Ray3d ray(Vector3dd(10, 1, 1), Vector3dd(0, 0, -1));
		EXPECT_FALSE(algo.calculateIntersection(ray, triangle, tolerance));
	}
	*/
}