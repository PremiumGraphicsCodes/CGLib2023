#include "MVPFluidView.h"

#include "MVPFluidScene.h"
#include "../Fluid/MVPFluidSolver.h"

#include "Renderer.h"

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
	boundaryView("Boundary"),
	pressureCoeView("PressureCoe", 500.f),
	viscosityCoeView("ViscosityCoe", 50.0f),
	timeStepView("TimeStep", 0.01f),
	radiusView("SearchRadius", 2.00f),
	externalForceView("ExternalForce", Vector3dd(0.0, -9.8, 0.0))
{
	boundaryView.setValue(Box3df(Vector3dd(0, 0.0, 0.0), Vector3dd(100.0, 1000.0, 40.0)));

	startButton.setFunction([=]() { onStart(); });
	add(&startButton);

	resetButton.setFunction([=]() { onReset(); });
	add(&resetButton);

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
	auto preseter = std::make_unique<MVPFluidPresenter>(fluidScene, renderer->getPointRenderer());
	preseter->build();
	fluidScene->setPresenter(std::move(preseter));

	world->getRootScene()->addScene(fluidScene);

	animator = new MVPFluidAnimator();
	animator->setScene(fluidScene);
	world->addAnimator(animator);

	this->onReset();
}

void MVPFluidView::onReset()
{
	auto fluid = std::make_unique<MVPFluid>();
	fluid->setPressureCoe(this->pressureCoeView.getValue());
	fluid->setViscosityCoe(this->viscosityCoeView.getValue());

	{
		const auto radius = 1.0;
		const auto length = radius * 0.5;
		for (int i = 0; i < 20; ++i) {
			for (int j = 0; j < 20; ++j) {
				for (int k = 0; k < 20; ++k) {
					//auto mp = new MVPVolumeParticle(radius*2.0, Vector3dd(i * length, j * length, k * length));
					const auto p = Vector3dd(i * length, j * length, k * length);
					auto mp = fluid->create(p, length, 0.25f, 300.0f);
					fluid->add(mp);
				}
			}
		}
	}

	auto solver = std::make_unique<MVPFluidSolver>();
	solver->setMaxTimeStep(timeStepView.getValue());
	solver->addBoundary(boundaryView.getValue());
	solver->setExternalForce(Vector3df(0.0f, -9.8f, 0.0f));
	solver->addFluidScene(fluid.get());

	this->fluidScene->setFluid(std::move(fluid));
	this->animator->setSolver(std::move(solver));
	this->animator->setTimeStep(timeStepView.getValue());
}

