#include "MVPFluidView.h"

#include "MVPFluidScene.h"
#include "../Fluid/MVPFluidSolver.h"
#include "../Fluid/MVPVolumeParticle.h"

#include "Renderer.h"

#include <random>

using namespace Crystal::Math;
using namespace Crystal::Scene;
using namespace Crystal::UI;
using namespace Crystal::Physics;

MVPFluidView::MVPFluidView(const std::string& name, World* model, Renderer* renderer) :
	IView(name),
	world(model),
	renderer(renderer),
	startButton("Start"),
	resetButton("Reset"),
	applyButton("Apply"),
	boundaryView("Boundary"),
	pressureCoeView("PressureCoe", 500.f),
	viscosityCoeView("ViscosityCoe", 50.0f),
	timeStepView("TimeStep", 0.01f),
	radiusView("SearchRadius", 1.00f),
	externalForceView("ExternalForce", Vector3dd(0.0, -9.8, 0.0))
{
	boundaryView.setValue(Box3df(Vector3dd(1.0, 0.0, 1.0), Vector3dd(50.0, 1000.0, 20.0)));

	startButton.setFunction([=]() { onStart(); });
	add(&startButton);

	resetButton.setFunction([=]() { onReset(); });
	add(&resetButton);

	applyButton.setFunction([=]() { onApply(); });
	add(&applyButton);

	add(&boundaryView);
	add(&pressureCoeView);
	add(&viscosityCoeView);
	add(&timeStepView);
	add(&radiusView);
	add(&externalForceView);
}

void MVPFluidView::onStart()
{
	fluidScene = new MVPFluidScene();
	auto preseter = new MVPFluidPresenter(fluidScene, renderer->getPointRenderer());
	preseter->build();
	fluidScene->addPresenter(std::move(preseter));

	world->getRootScene()->addScene(fluidScene);

	animator = new MVPFluidAnimator();
	animator->setScene(fluidScene);
	world->addAnimator(animator);

	this->onReset();
}

void MVPFluidView::onReset()
{
	auto fluid = std::make_unique<MVPFluid>();

	/*
	{
		const auto radius = 0.5;
		const auto length = radius * 2.0;
		for (int i = 0; i < 20; ++i) {
			for (int j = 0; j < 20; ++j) {
				for (int k = 0; k < 20; ++k) {
					//auto mp = new MVPVolumeParticle(radius*2.0, Vector3dd(i * length, j * length, k * length));
					const auto p = Vector3dd(i * length, j * length, k * length);
					auto mp = fluid->create(p, length, 0.25f);
					mp->setPressureCoe(this->pressureCoeView.getValue());
					mp->setViscosityCoe(this->viscosityCoeView.getValue());
					fluid->add(mp);
				}
			}
		}
	}
	*/
	Box3df box(Vector3df(0, 0, 0), Vector3df(20, 20, 20));
	std::mt19937 mt{ std::random_device{}() };
	std::uniform_real_distribution<float> dist(0.0, 1.0);
	for (int i = 0; i < 10000; ++i) {
		const auto u = dist(mt);
		const auto v = dist(mt);
		const auto w = dist(mt);
		const auto pos =  box.getPosition(u, v, w);
		auto mp = fluid->create(pos, 1.0, 0.25f);
		mp->setPressureCoe(this->pressureCoeView.getValue());
		mp->setViscosityCoe(this->viscosityCoeView.getValue());
		fluid->add(mp);
	}

	auto solver = std::make_unique<MVPFluidSolver>();
	solver->setMaxTimeStep(timeStepView.getValue());
	solver->setBoundary(boundaryView.getValue());
	solver->setExternalForce(Vector3df(0.0f, -9.8f, 0.0f));
	solver->setEffectLength(this->radiusView.getValue());
	solver->addFluidScene(fluid.get());

	this->fluidScene->setFluid(std::move(fluid));
	this->animator->setSolver(std::move(solver));
	this->animator->setTimeStep(timeStepView.getValue());
}

void MVPFluidView::onApply()
{
	auto solver = this->animator->getSolver();
	solver->setBoundary(boundaryView.getValue());
	solver->setMaxTimeStep(timeStepView.getValue());
}