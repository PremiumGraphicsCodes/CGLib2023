#pragma once

#include "CGLib/Math/Vector2d.h"

#include "IUICtrl.h"
#include "IRenderer.h"
#include <memory>

namespace Crystal {
	namespace UI {
		class IUICtrl;

class Canvas : public IMouseListener
{
public:
	Canvas();

	Canvas(std::unique_ptr<IUICtrl> ctrl, IRenderer* renderer) :
		ctrl(std::move(ctrl)),
		renderer(renderer)
	{
	}

	virtual ~Canvas() {}

	void setUICtrl(std::unique_ptr<IUICtrl> ctrl) { this->ctrl = std::move(ctrl); }

	void setRenderer(IRenderer* renderer) { this->renderer = renderer; }

	virtual void onLeftButtonDown(const Math::Vector2df& position) override;

	virtual void onLeftButtonUp(const Math::Vector2df& position) override;

	virtual void onRightButtonDown(const Math::Vector2df& position) override;

	virtual void onRightButtonUp(const Math::Vector2df& position) override;

	virtual void onMiddleButtonDown(const Math::Vector2df& position) override;

	virtual void onMiddleButtonUp(const Math::Vector2df& position) override;

	virtual void onLeftDragging(const Math::Vector2df& position) override;

	virtual void onRightDragging(const Math::Vector2df& position) override;

	virtual void onMiddleDragging(const Math::Vector2df& position) override;

	virtual void onWheel(const float scale) override;

	void render(const int width, const int height) {
		this->renderer->render(width, height);
	}

	IRenderer* getRenderer() { return renderer; }

private:
	std::unique_ptr<IUICtrl> ctrl;
	IRenderer* renderer;
};

	}
}