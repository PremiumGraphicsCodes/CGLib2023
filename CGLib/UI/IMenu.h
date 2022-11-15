#pragma once

#include "CGLib/UI/IWindow.h"

namespace Crystal {
	namespace UI {

		class IMenu : public IWindow
		{
		public:
			IMenu(const std::string& name) :
				IWindow(name)
			{}

			virtual ~IMenu() {};

		protected:
			void onShow() override;

		private:
		};

	}
}