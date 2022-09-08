#pragma once
#include "MenuUtils.h"

namespace GamemodeMenu {

	enum class GamemodeMenuOptions {
		SINGLEPLAYER,
		MULTIPLAYER,
		TOGGLEPOWERUPS,
		RETURNTOMENU,
		COUNT
	};

	void MenuLoop();
	void InitMenu();
}