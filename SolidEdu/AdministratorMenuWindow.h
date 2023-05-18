#pragma once

#include "IWindow.h"
#include <algorithm>
#include <iostream>

namespace solid_edu
{
	class AdministratorMenuWindow : public IWindow
	{
	public:
		std::unique_ptr<IWindow> runThenReturnWindow() override;
	};
}
