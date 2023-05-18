#pragma once

namespace solid_edu
{
	class IMessageReader
	{
	public:
		virtual void moreMessages() = 0;
		virtual void readMessages() = 0;

		virtual ~IMessageReader() = 0 {};
	};
}
