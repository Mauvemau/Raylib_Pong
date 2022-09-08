#pragma once
#include "MenuUtils.h"

namespace MainMenu {
	enum class MainMenuOptions { // Las diferentes opciones presentes en el main menu.
		PLAY,
		HOW2PLAY, // Menu de instrucciones.
		SETTINGS,
		EXIT,
		COUNT
	};

	void MenuLoop();
	void InitMenu();
}