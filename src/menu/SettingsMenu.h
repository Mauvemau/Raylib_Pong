#pragma once
#include "MenuUtils.h"

namespace Settings {
	enum class SettingsOptions {
		CHANGERESOLUTION,
		FULLSCREEN,
		RETURNTOMENU,
		COUNT
	};

	enum class Resolutions {
		NORMAL,
		BIGGER,
		WIDE,
		TALL
	};

	struct Resolution {
		int width;
		int height;
	};

	void MenuLoop();
	void ResetSettings(); // Reinicia las variables de las settings, usar una unica vez.
	void InitMenu();
}