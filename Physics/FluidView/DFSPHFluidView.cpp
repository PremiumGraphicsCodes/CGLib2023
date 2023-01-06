#include "DFSPHFluidView.h"

#include "DFSPHFluidScene.h"
#include "DFSPHFluidPresenter.h"
#include "../Fluid/DFSPHSolver.h"
#include "../Fluid/DFSPHParticle.h"

using namespace Crystal::Math;
using namespace Crystal::Scene;
using namespace Crystal::UI;
using namespace Crystal::Physics;

DFSPHFluidView::DFSPHFluidView(const std::string& name, World* model, Renderer* renderer) :
	IOkCancelView(name),
	model(model),
	renderer(renderer),
	startButton("Start"),
	resetButton("Reset"),
	timeStepView("TimeStep", 0.01f),
	radiusView("Radius", 1.0f),
	effectLengthView("EffectLength", 2.25f),
	densityView("Density", 1.0f),
	boundaryView("Boundary"),
	stiffnessView("Stiffness", 0.05f),
	vicsocityView("Viscosity", 0.1f)
{
	resetButton.setFunction([=]() { onReset(); });
	boundaryView.setValue(Box3df(Vector3dd(0, 0.0, 0.0), Vector3dd(100.0, 1000.0, 40.0)));

	add(&resetButton);
	add(&timeStepView);
	add(&radiusView);
	add(&densityView);
	add(&effectLengthView);
	add(&boundaryView);
	add(&stiffnessView);
	add(&vicsocityView);
}

void DFSPHFluidView::onOk()
{
	this->fluidScene = new DFSPHFluidScene();

	auto presenter = new DFSPHFluidPresenter(fluidScene, renderer->getPointRenderer());
	presenter->build();
	this->fluidScene->addPresenter(std::move(presenter));

	model->getRootScene()->addScene(fluidScene);

	animator = new DFSPHAnimator();
	animator->setScene(fluidScene);
	model->addAnimator(animator);

	this->onReset();
}

void DFSPHFluidView::onReset()
{
	auto fluid = std::make_unique<DFSPHFluid>();
	fluid->setEffectLength(this->effectLengthView.getValue());
	fluid->density = (this->densityView.getValue());
	fluid->pressureCoe = (this->stiffnessView.getValue());
	fluid->viscosityCoe = (this->vicsocityView.getValue());

	const auto radius = 1.0;
	const auto length = radius * 2.0;
	for (int i = 0; i < 20; ++i) {
		for (int j = 0; j < 20; ++j) {
			for (int k = 0; k < 20; ++k) {
				auto mp = std::make_unique<DFSPHParticle>(Vector3df(i * length, j * length, k * length), radius, fluid.get());
				fluid->addParticle(std::move(mp));
			}
		}
	}

	auto solver = std::make_unique<DFSPHSolver>();
	solver->setTimeStep(timeStepView.getValue());
	solver->setBoundary(boundaryView.getValue());
	solver->setExternalForce(Vector3df(0.0f, -9.8f, 0.0f));
	solver->add(fluid.get());

	this->fluidScene->setFluid(std::move(fluid));
	this->animator->setSolver(std::move(solver));
	this->animator->setTimeStep(timeStepView.getValue());
}