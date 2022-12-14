#pragma once

#include "CGLib/Math/Matrix2d.h"
#include "CGLib/Math/Matrix3d.h"
#include "CGLib/Math/Matrix4d.h"

#include "CGLib/Math/Vector2d.h"
#include "CGLib/Math/Vector3d.h"
#include "CGLib/Math/Vector4d.h"

#include "../ThirdParty/eigen-3.4.0/Eigen/Eigen"


namespace Crystal {
	namespace Numerics {

class Converter
{
public:
	static Eigen::Matrix2d toEigen(const Math::Matrix2dd& src);

	static Eigen::Matrix3d toEigen(const Math::Matrix3dd& src);

	static Eigen::Matrix4d toEigen(const Math::Matrix4dd& src);

	static Eigen::Vector2d toEigen(const Math::Vector2dd& src);

	static Eigen::Vector3d toEigen(const Math::Vector3dd& src);

	static Eigen::Vector4d toEigen(const Math::Vector4dd& src);

	static Math::Matrix2dd fromEigen(const Eigen::Matrix2d& src);

	static Math::Matrix3dd fromEigen(const Eigen::Matrix3d& src);

	static Math::Matrix4dd fromEigen(const Eigen::Matrix4d& src);

	static Math::Vector2dd fromEigen(const Eigen::Vector2d& src);

	static Math::Vector3dd fromEigen(const Eigen::Vector3d& src);

	static Math::Vector4dd fromEigen(const Eigen::Vector4d& src);
};
	}
}