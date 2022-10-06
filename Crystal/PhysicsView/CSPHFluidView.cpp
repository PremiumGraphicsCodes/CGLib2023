#include "CSPHFluidView.h"

using namespace Crystal::Math;
//using namespace Crystal::Shape;
using namespace Crystal::Scene;
using namespace Crystal::UI;
using namespace Crystal::Physics;


CSPHFluidView::CSPHFluidView(const std::string& name, WorldBase* world, RendererBase* renderer) :
	IOkCancelView(name),
	startButton("Start"),
	resetButton("Reset"),
	//	nextButton("Next"),
	timeStepView("TimeStep", 0.001f),
	pressureCoeView("PressureCoe", 1.0f),
	viscosityView("Viscosity", 1.0f),
	densityView("Density", 10.0f),
	boundaryView("Boundary"),
	world(world),
	renderer(renderer)
{
	boundaryView.setValue(Box3df(Vector3dd(-100, 0, -100), Vector3dd(100, 1000, 100)));
	resetButton.setFunction([=]() { onReset(); });
	add(&resetButton);
	add(&timeStepView);
	add(&pressureCoeView);
	add(&viscosityView);
	add(&densityView);
	add(&boundaryView);
}

void CSPHFluidView::onOk()
{
	fluidScene = new CSPHFluidScene();
	world->getRootScene()->addScene(fluidScene);

	fluidScene->getPresenter()->build();

	animator = new CSPHAnimator();
	world->addAnimator(animator);

	this->onReset();

	//getWorld()->addAnimation(simulator);
}

void CSPHFluidView::onReset()
{
	auto fluid = std::make_unique<CSPHFluid>();
	this->fluidScene->setFluid(std::move(fluid));

	const auto radius = 1.0f;
	const auto length = radius * 2.0;
	const auto effectLength = length * 1.25;
	fluid->setPressureCoe( pressureCoeView.getValue() );
	fluid->setVicosityCoe( viscosityView.getValue() );
	fluid->setEffectLength(effectLength);
	//solver->setEffectLenth(effectLength);
	fluid->setDensity( densityView.getValue() );
	//solver->setTimeStep(timeStepView.getValue());
	//solver->setBoundary(boundaryView.getValue());
	//solver->setExternalForce(Vector3df(0.0, -9.8, 0.0));

	for (int i = 0; i < 10; ++i) {
		for (int j = 0; j < 5; ++j) {
			for (int k = 0; k < 10; ++k) {
				auto mp = std::make_unique<CSPHParticle>(Vector3df(i * length, j * length, k * length), radius, fluid.get());
				fluid->addParticle(std::move(mp));
			}
		}
	}
}