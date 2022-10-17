#include "MVPSamplerView.h"
#include "../Fluid/MVPFluid.h"
#include "../Fluid/MVPSampler.h"
#include "../Fluid/MVPVolumeParticle.h"

using namespace Crystal::Math;
using namespace Crystal::Scene;
using namespace Crystal::Physics;
using namespace Crystal::UI;

MVPSamplerView::MVPSamplerView(const std::string& name, World* model, Renderer* canvas) :
	IView(name),
	world(model),
	renderer(canvas),
	splitButton("Split"),
	mergeButton("Merge")
{
	splitButton.setFunction([=]() { onSplit(); });
	add(&splitButton);

	mergeButton.setFunction([=]() { onMerge(); });
	add(&mergeButton);
}

void MVPSamplerView::onSplit()
{

}

void MVPSamplerView::onMerge()
{
	MVPFluid fluid;
	{
		const auto radius = 0.20;
		const auto length = radius * 1.00;
		for (int i = 0; i < 10; ++i) {
			for (int j = 0; j < 10; ++j) {
				for (int k = 0; k < 10; ++k) {
					const auto p = Vector3dd(i * length, j * length, k * length);
					auto vp = new MVPVolumeParticle(radius * 2.0, Vector3df(i * length, j * length, k * length));
					auto mp = new MVPMassParticle(vp, p, 1.0f);
					mp->setParent(vp);
					vp->addMassParticle(mp);
					fluid.add(vp);
				}
			}
		}
	}
	//getWorld()->getScenes()->addScene(this->fluidScene);
	//fluidScene->getPresenter()->createView(getWorld()->getRenderer());

	MVPSampler sampler;
	sampler.merge({ &fluid }, 0.80);
}