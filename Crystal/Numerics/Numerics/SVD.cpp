#include "pch.h"

#include "SVD.h"

#include "Converter.h"

using namespace Crystal::Numerics;

#include <iostream>
//#include <Eigen/SVD>

//using namespace Crystal::Numerics;

using namespace std;
using namespace Eigen;
using namespace Crystal::Math;

SVD2d::Result SVD2d::calculate(const Matrix2dd& lhs)
{
	SVD2d::Result result;
	Eigen::Matrix2d A = Converter::toEigen(lhs);
	SelfAdjointEigenSolver<Eigen::Matrix2d> eigensolver(A);
	if (eigensolver.info() != Success) {
		result.isOk = false;
	}
	result.isOk = true;
	result.eigenValues = Converter::fromEigen(eigensolver.eigenvalues());
	result.eigenVectors = Converter::fromEigen(eigensolver.eigenvectors());
	return result;
}
