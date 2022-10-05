#include "gtest/gtest.h"
#include "../Space/IntersectionCalculator.h"

#include "CGLib/Math/Ray3d.h"
#include "CGLib/Math/Sphere3d.h"
#include "CGLib/Math/Plane3d.h"
#include "CGLib/Math/Triangle3d.h"
#include "CGLib/Math/Box3d.h"

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
	const auto found = c.calculate(ray, sphere, tolerance);
	EXPECT_EQ(found.size(), 2);
	EXPECT_FLOAT_EQ(9.0f, found[0]);
	EXPECT_FLOAT_EQ(11.0f, found[1]);
}

TEST(IntersectionCalculatorTest, TestRayAndPlane)
{
	IntersectionCalculator<float> c;
	Ray3df ray(Vector3df(0, 0, 0), Vector3df(1, 0, 0));
	Plane3df plane(Vector3df(10, 0, 0), Vector3df(-1, 0, 0));
	const auto found = c.calculate(ray, plane, tolerance);
	EXPECT_EQ(found.size(), 1);
	Vector3df expected(10, 0, 0);
	EXPECT_FLOAT_EQ(10.0f, found[0]);
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

TEST(IntersectionCalculatorTest, TestRayAndBox)
{
	IntersectionCalculator<float> algo;
	const Ray3df ray(Vector3dd(-5, 5, 5), Vector3dd(20, 0, 0));

	const Box3df box1(Vector3dd(0, 0, 0), Vector3dd(10, 10, 10));
	EXPECT_TRUE(algo.calculateIntersection(ray, box1, tolerance));
	EXPECT_EQ(2, algo.getIntersections().size());
	EXPECT_TRUE(::areSame(Vector3df(0, 5, 5), algo.getIntersections()[0], tolerance));
	EXPECT_TRUE(::areSame(Vector3df(10, 5, 5), algo.getIntersections()[1], tolerance));

	const Box3df box2(Vector3df(50, 50, 50), Vector3df(100, 100, 100));
	EXPECT_FALSE(algo.calculateIntersection(ray, box2, tolerance));
}