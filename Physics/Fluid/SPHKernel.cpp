#include "SPHKernel.h"

using namespace Crystal::Math;
using namespace Crystal::Physics;

namespace {
	static const float PIf = 3.14159265358979323846f;
}

SPHKernel::SPHKernel(const float effectLength) :
	effectLength(effectLength)
{
	this->poly6KernelConstant = 315.0f / (64.0f * PIf * pow(effectLength, 9.0f));
	this->spikyKernelGradConstant = 45.0f / (::PIf * pow(effectLength, 6.0f));
	this->effectLengthSquared = effectLength * effectLength;
}

float SPHKernel::getPoly6Kernel(const float distance)
{
	if (distance > effectLength) {
		return 0.0f;
	}
	return this->poly6KernelConstant * pow(effectLength * effectLength - distance * distance, 3.0f);
}

float SPHKernel::getPoly6Kernel2(const float distanceSquared)
{
	if (distanceSquared > effectLengthSquared) {
		return 0.0f;
	}
	const auto a = effectLengthSquared - distanceSquared;
	return this->poly6KernelConstant * a * a * a;
}

/*
float SPHKernel::getPoly6Kernel(const float distance, const float effectLength)
{
	if (distance > effectLength) {
		return 0.0f;
	}
	const auto poly6Constant = 315.0f / (64.0f * PI * pow(effectLength, 9));
	return poly6Constant * pow(effectLength * effectLength - distance * distance, 3);
}
*/

Vector3df SPHKernel::getPoly6KernelGradient(const Vector3df& distanceVector)
{
	const auto distance = glm::length(distanceVector);
	if (distance > effectLength) {
		return Vector3df(0, 0, 0);
	}
	const auto poly6ConstantGradient = 945.0f / (32.0f * PIf * pow(effectLength, 9.0f));
	const auto factor = poly6ConstantGradient * pow(effectLength * effectLength - distance * distance, 2.0f);
	return distanceVector * factor;
}

float SPHKernel::getPoly6KernelGradientCoe(const float distance)
{
	const auto poly6ConstantGradient = 945.0f / (32.0f * PIf * pow(effectLength, 9.0f));
	return poly6ConstantGradient * pow(effectLength * effectLength - distance * distance, 2.0f);
}

float SPHKernel::getPoly6KernelLaplacian(const float distance)
{
	if (distance > effectLength) {
		return 0.0f;
	}
	const auto poly6ConstantLaplacian = 945.0f / (32.0f * PIf * pow(effectLength, 9.0f));
	return poly6ConstantLaplacian * (effectLength * effectLength - distance * distance)
		* (42.0f * distance * distance - 18.0f * effectLength * effectLength);
}

Vector3df SPHKernel::getSpikyKernelGradient(const Vector3df& distanceVector) const
{
	const auto distance = glm::length(distanceVector);
	if (distance > effectLength) {
		return Vector3df(0, 0, 0);
	}
	return distanceVector * this->spikyKernelGradConstant * pow(effectLength - distance, 2.0f) / distance;
}

float SPHKernel::getSpikyKernelGradientWeight(const float distance)
{
	if (distance > effectLength) {
		return 0.0;
	}
	const auto constant = 45.0f / (PIf * pow(effectLength, 6.0f));
	return constant * pow(effectLength - distance, 2.0f) / distance;
}

/*
Vector3df SPHKernel::getSpikyKernelGradient(const Vector3df& distanceVector)
{
	const auto distance = glm::length(distanceVector);
	if (distance > effectLength) {
		return Vector3df(0, 0, 0);
	}
	const auto constant = 45.0f / (PIf * pow(effectLength, 6));
	return distanceVector * constant * pow(effectLength - distance, 2) / distance;
}
*/

float SPHKernel::getViscosityKernelLaplacian(const float distance)
{
	if (distance > effectLength) {
		return 0.0f;
	}
	const auto constant = 45.0f / (PIf * pow(effectLength, 6.0f));
	return (effectLength - distance) * constant;
}

float SPHKernel::getCubicSpline(const float distance) const
{
	const auto q = distance * 2 / (effectLength);
	const auto coe = effectLength * effectLength * effectLength * 3.0f / PIf;

	if (q < 1) {
		return coe * (2.0f / 3.0f - q * q + 0.5f * q * q * q);
	}
	else if (q < 2) {
		return coe * (std::pow(2.0f - q, 3.0f) / 6.0f);
	}
	else {
		return 0;
	}
}

float SPHKernel::getCubicSpline(const Vector3df& v) const
{
	const auto q = glm::length(v) / effectLength;
	const auto numerator = getCubicSpline(q);
	const auto denominator = std::pow(effectLength, 3.0f);
	return numerator / denominator;
}

Vector3df SPHKernel::getCubicSplineGradient(const Vector3df& distanceVector)
{
	const auto length = glm::length(distanceVector);
	const auto l = 48.0f / (PIf * effectLength * effectLength * effectLength);
	const auto q = length / effectLength;
	const auto grad = distanceVector * (1.0f / (length * effectLength));
	if (q < 0.01f) {
		return Vector3df(0, 0, 0);
	}
	else if (q < 0.5f) {
		return l * q * (3.0f * q - 2.0f) * grad;
	}
	else if (q < 1.0f) {
		const auto f = 1.0f - q;
		return l * (-f * f) * grad;
	}
	else {
		return Vector3df(0, 0, 0);
	}
}