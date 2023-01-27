
#include "PBSPHParticle.h"

#include "SPHKernel.h"

#include "PBSPHFluid.h"

using namespace Crystal::Math;
using namespace Crystal::Physics;


PBSPHParticle::PBSPHParticle(const Vector3df& center, const float radius, PBSPHFluid* scene) :
	position(center),
	radius(radius),
	scene(scene),
	temperature(300.0f),
	enthalpy(0.0f)
{
	this->density = scene->getRestDensity();
}

void PBSPHParticle::init()
{
	density = 0.0;
	dx = Math::Vector3df(0.0f, 0.0f, 0.0f);
	normal = Math::Vector3df(0.0f, 0.0f, 0.0f);
	force = Math::Vector3df(0.0f, 0.0f, 0.0f);
	this->predictPosition = this->position;

	this->enthalpy = 0.0f;
}

float PBSPHParticle::getDensityRatio() const
{
	/*
	if (scene->isBoundary()) {
		return 10.0f;
	}
	*/
	return density / scene->getRestDensity();
}

float PBSPHParticle::getMass() const
{
	const auto diameter = radius * 2.0f;
	return scene->getRestDensity() * diameter * diameter * diameter;
}

float PBSPHParticle::getVolume() const
{
	return getMass() / density;
}

float PBSPHParticle::getRestVolume() const
{
	return getMass() / scene->getRestDensity();
}

void PBSPHParticle::setDefaultDensity()
{
	this->density = scene->getRestDensity();
}

void PBSPHParticle::forwardTime(const float timeStep)
{
	const auto& acc = getAccelaration();
	this->velocity += (acc * timeStep);
	this->position += (this->velocity * timeStep);
}

void PBSPHParticle::addExternalForce(const Vector3df& externalForce)
{
	if (scene->isBoundary()) {
		return;
	}
	this->force += externalForce * scene->getRestDensity();
}

void PBSPHParticle::addSelfDensity()
{
	this->addDensity(getKernel()->getPoly6Kernel(0.0) * this->getMass());
}

void PBSPHParticle::addDensity(const PBSPHParticle& rhs)
{
	const float distance = glm::distance(this->getPredictPosition(), rhs.getPredictPosition());
	this->addDensity(scene->getKernel()->getPoly6Kernel(distance) * rhs.getMass());
}

void PBSPHParticle::addDensity(const float distance, const float mass)
{
	this->addDensity(getKernel()->getPoly6Kernel(distance) * mass);
}

void PBSPHParticle::predictPosition_(const float dt)
{
	if (scene->isBoundary()) {
		return;
	}
	this->position = this->predictPosition;
	this->velocity += dt * this->force;
	this->predictPosition += dt * this->velocity;
}

void PBSPHParticle::updatePredictPosition()
{
	if (scene->isBoundary()) {
		return;
	}
	this->predictPosition += dx;
}

void PBSPHParticle::updateVelocity(const float dt)
{
	if (scene->isBoundary()) {
		return;
	}
	this->velocity = (this->predictPosition - this->position) / dt;
}

void PBSPHParticle::updatePosition()
{
	if (scene->isBoundary()) {
		return;
	}
	this->position = this->predictPosition;
}

void PBSPHParticle::updateHeat(const float dt)
{
	if (scene->isBoundary()) {
		return;
	}
	// 熱エネルギーが追加され続けてしまうので減衰させる．
	// 厳密に処理するなら熱エネルギー専用のBoundaryHanldingが本来必要．
	this->enthalpy -= (this->temperature - 300.0f) * 0.01f;

	this->temperature += this->enthalpy * dt;
}

void PBSPHParticle::addPositionCorrection(const Vector3df& distanceVector)
{
	this->dx += distanceVector;
	//const auto pc = 1.0f / this->constant->getDensity() * (this->densityConstraint + this->densityConstraint) * kernel.getSpikyKernelGradient(distanceVector, constant->getEffectLength());
	//this->positionCorrection += pc;
}

float PBSPHParticle::getEffectLength() const
{
	return scene->getKernel()->getEffectLength();
}

void PBSPHParticle::calculatePressure(const PBSPHParticle& rhs)
{
	const auto v = this->getPredictPosition() - rhs.getPredictPosition();
	const auto weight = getKernel()->getPoly6KernelGradient(v);
	const auto c = this->getConstraint() + rhs.getConstraint();
	dx += c * weight / scene->getRestDensity() * scene->getStiffness();//0.05f;
}

void PBSPHParticle::calculateViscosity(const PBSPHParticle& rhs)
{
	const auto v = this->getPredictPosition() - rhs.getPredictPosition();
	const auto vel = rhs.getVelocity() - this->velocity;
	const auto weight = getKernel()->getViscosityKernelLaplacian(glm::length(v));
	this->xvisc += vel * weight * scene->getViscosity();
}

float PBSPHParticle::getConstraint() const
{
	return std::max(getDensityRatio() - 1.0f, 0.0f);
}

SPHKernel* PBSPHParticle::getKernel()
{
	return scene->getKernel();
}

void PBSPHParticle::calculateHeatDiffusion(const PBSPHParticle& rhs)
{
	const auto v = this->getPredictPosition() - rhs.getPredictPosition();
	const auto dt = rhs.temperature - this->temperature;
	const auto weight = getKernel()->getViscosityKernelLaplacian(glm::length(v));
	this->enthalpy += dt * weight * scene->getHeatDiffuse();
}
