#pragma once

#include "IWindow.h"
#include "IMessageReader.h"
#include "IUser.h"
#include "IConversation.h"
#include <string>
#include <iostream>

namespace solid_edu
{
	class ConversationWindow : public IWindow
	{
	private:
		std::string aFriend;
		std::unique_ptr<IUser> user;
		std::unique_ptr<IConversation> conversation;
		std::unique_ptr<IMessageReader> messageReader;

	public:
		ConversationWindow(const std::string& aFriend, std::unique_ptr<IUser> user);

		std::unique_ptr<IWindow> runThenReturnWindow() override;
	};
}
