#pragma once

#include "CGLib/Math/Vector2d.h"

#include "IUICtrl.h"
#include <memory>

namespace Crystal {
	namespace UI {
		class IUICtrl;

		class Canvas : public IMouseListener
		{
		public:
			Canvas();

			virtual ~Canvas() {}

			void setUICtrl(IUICtrl* ctrl) { this->ctrl.reset(ctrl); }

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

		private:
			std::unique_ptr<IUICtrl> ctrl;
		};

	}
}