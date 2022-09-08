#pragma once

namespace PauseMenu {

	enum class PauseMenuOptions {
		RESUME, // Ranudar la partida.
		RESTART, // Reiniciar la partida.
		RETURNTOMENU, // Salir de la partida y volver al menu principal.
		COUNT
	};

	void DrawMenu();
	void MenuInput();
	void InitMenu();
}