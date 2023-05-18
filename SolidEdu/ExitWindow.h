#pragma once
#include "IWindow.h"

namespace solid_edu
{
	class ExitWindow : public IWindow
	{
	public:
		std::unique_ptr<IWindow> runThenReturnWindow() override { return nullptr; };
	};
}
