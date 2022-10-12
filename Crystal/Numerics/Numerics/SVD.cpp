#include "pch.h"

#include "SVD.h"

#include "Converter.h"

using namespace Crystal::Numerics;

#include <iostream>
#include "../ThirdParty/eigen-3.4.0/Eigen/Dense"
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

SVD3d::Result SVD3d::calculate(const Matrix3dd& lhs)
{
	SVD3d::Result result;
	Eigen::Matrix3d A = Converter::toEigen(lhs);
	SelfAdjointEigenSolver<Eigen::Matrix3d> eigensolver(A);
	if (eigensolver.info() != Success) {
		result.isOk = false;
	}
	result.isOk = true;
	result.eigenValues = Converter::fromEigen(eigensolver.eigenvalues());
	result.eigenVectors = Converter::fromEigen(eigensolver.eigenvectors());
	return result;
}

SVD3d::Result SVD3d::calculateJacobi(const Matrix3dd& matrix)
{
	SVD3d::Result result;
	Eigen::Matrix3d A = Converter::toEigen(matrix);
	Eigen::JacobiSVD<Eigen::Matrix3d> svd(A, Eigen::ComputeFullU);
	const auto& R = svd.matrixU();
	result.isOk = true;
	result.eigenValues = Converter::fromEigen(svd.singularValues());
	result.eigenVectors = Converter::fromEigen(svd.matrixU());
	return result;
}