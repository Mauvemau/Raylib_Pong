#pragma once
#include "MenuUtils.h"

namespace GameOverMenu {

	enum class GameOverMenuOptions {
		PLAYAGAIN,
		RETURNTOMENU,
		COUNT
	};

	void MenuLoop();
	void InitMenu();
}