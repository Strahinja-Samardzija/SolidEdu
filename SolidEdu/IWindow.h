#pragma once

#include "IUser.h"
#include <iostream>
#include <string>
#include <memory>

namespace solid_edu
{
	class IWindow
	{
	public:
		virtual std::unique_ptr<IWindow> runThenReturnWindow() = 0;

		virtual ~IWindow() = 0 {};
	};
}
