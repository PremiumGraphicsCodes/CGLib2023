#include "PBSPHFlameView.h"

#include "PBSPHFluidScene.h"
#include "PBSPHFluidPresenter.h"
#include "../Fluid/PBSPHSolver.h"
#include "../Fluid/PBSPHParticle.h"

using namespace Crystal::Math;
using namespace Crystal::Scene;
using namespace Crystal::UI;
using namespace Crystal::Physics;

PBSPHFlameView::PBSPHFlameView(const std::string& name, World* model, Renderer* renderer) :
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
	vicsocityView("Viscosity", 0.1f),
	heatDiffuseView("HeatDiffuse", 10.0f)
{
	resetButton.setFunction([=]() { onReset(); });
	boundaryView.setValue(Box3df(Vector3dd(0.0, 0.0, 0.0), Vector3dd(40.0, 50.0, 40.0)));

	add(&resetButton);
	add(&timeStepView);
	add(&radiusView);
	add(&densityView);
	add(&effectLengthView);
	add(&boundaryView);
	add(&stiffnessView);
	add(&vicsocityView);
	add(&heatDiffuseView);
}

void PBSPHFlameView::onOk()
{
	{
		this->fluidScene = new PBSPHFluidScene();

		auto presenter = new PBSPHFluidPresenter(fluidScene, renderer->getPointRenderer());
		presenter->build();
		this->fluidScene->addPresenter(std::move(presenter));

		model->getRootScene()->addScene(fluidScene);
	}

	{
		this->sourceScene = new PBSPHFluidScene();

		auto presenter = new PBSPHFluidPresenter(sourceScene, renderer->getPointRenderer());
		presenter->build();
		this->fluidScene->addPresenter(std::move(presenter));

		model->getRootScene()->addScene(sourceScene);
	}

	animator = new PBSPHAnimator();
	animator->setScene(fluidScene);
	model->addAnimator(animator);

	this->onReset();
}

void PBSPHFlameView::onReset()
{
	auto fluid = std::make_unique<PBSPHFluid>();
	fluid->setEffectLength(this->effectLengthView.getValue());
	fluid->setRestDensity(this->densityView.getValue());
	fluid->setStiffness(this->stiffnessView.getValue());
	fluid->setVicsosity(this->vicsocityView.getValue());
	fluid->setHeatDiffuse(this->heatDiffuseView.getValue());

	const auto radius = 1.0;
	const auto length = radius * 2.0;
	for (int i = 0; i < 20; ++i) {
		for (int j = 0; j < 20; ++j) {
			for (int k = 0; k < 20; ++k) {
				auto mp = std::make_unique<PBSPHParticle>(Vector3df(i * length, j * length, k * length), radius, fluid.get());
				fluid->addParticle(std::move(mp));
			}
		}
	}

	auto source = std::make_unique<PBSPHFluid>();
	source->setEffectLength(this->effectLengthView.getValue());
	source->setRestDensity(this->densityView.getValue());
	source->setStiffness(this->stiffnessView.getValue());
	source->setVicsosity(this->vicsocityView.getValue());
	source->setHeatDiffuse(this->heatDiffuseView.getValue());
	source->setIsBoundary(true);

	for (int i = 5; i < 15; ++i) {
		for (int j = -2; j < 0; ++j) {
			for (int k = 5; k < 15; ++k) {
				auto mp = std::make_unique<PBSPHParticle>(Vector3df(i * length, j * length, k * length), radius, source.get());
				mp->setTemperature(1500.0f);
				source->addParticle(std::move(mp));				
			}
		}
	}

	auto solver = std::make_unique<PBSPHSolver>();
	solver->setTimeStep(timeStepView.getValue());
	solver->setBoundary(boundaryView.getValue());
	solver->setExternalForce(Vector3df(0.0f, -9.8f, 0.0f));
	solver->add(fluid.get());
	solver->add(source.get());

	this->fluidScene->setFluid(std::move(fluid));
	this->sourceScene->setFluid(std::move(source));
	this->animator->setSolver(std::move(solver));
	this->animator->setTimeStep(timeStepView.getValue());
}