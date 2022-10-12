#include "PBSPHFluidSimulationView.h"

#include "PBSPHFluidScene.h"
#include "../Physics/PBSPHSolver.h"
#include "../Physics/PBSPHParticle.h"

using namespace Crystal::Math;
using namespace Crystal::Scene;
using namespace Crystal::UI;
using namespace Crystal::Physics;

PBSPHFluidSimulationView::PBSPHFluidSimulationView(const std::string& name, WorldBase* model, RendererBase* renderer) :
	IOkCancelView(name),
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

void PBSPHFluidSimulationView::onOk()
{
	/*
	auto world = getWorld();

	this->fluidScene = new PBFluidScene(getWorld()->getNextSceneId(), "Fluid");
	//this->boundaryScene = new PBFluidScene(getWorld()->getNextSceneId(), "Boundary");
	this->simulator = new PBSPHSolver();

	onReset();

	getWorld()->getScenes()->addScene(this->fluidScene);
	auto newId = this->fluidScene->getId();
	this->fluidScene->getPresenter()->createView(world->getRenderer());

	simulator->add(this->fluidScene);
	//simulator->add(this->boundaryScene);

	simulator->setExternalForce(Vector3df(0.0, -9.8, 0.0));

	getWorld()->addAnimation(simulator);
	*/
}

void PBSPHFluidSimulationView::onReset()
{
	/*
	//this->simulator->clear();
	this->fluidScene->clearParticles();
	this->fluidScene->setEffectLength(this->effectLengthView.getValue());
	this->fluidScene->setRestDensity(this->densityView.getValue());
	this->fluidScene->setStiffness(this->stiffnessView.getValue());
	this->fluidScene->setVicsosity(this->vicsocityView.getValue());

	const auto radius = 1.0;
	const auto length = radius * 2.0;
	for (int i = 0; i < 20; ++i) {
		for (int j = 0; j < 20; ++j) {
			for (int k = 0; k < 20; ++k) {
				auto mp = new PBSPHParticle(Vector3dd(i * length, j * length, k * length), radius, this->fluidScene);
				this->fluidScene->addParticle(mp);
			}
		}
	}


	simulator->setBoundary(boundaryView.getValue());
	simulator->setTimeStep(timeStepView.getValue());
	*/
}