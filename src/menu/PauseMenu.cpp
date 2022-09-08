#include "PauseMenu.h"
#include "MenuUtils.h"
#include "game/Game.h" // Para saber si el juego esta pausado y para reiniciarlo.
#include <iostream> // Para los errores de consola.

namespace PauseMenu {

	const int amountButtons = (int)PauseMenuOptions::COUNT;
	Button menuButtons[amountButtons];
	int menuCursor;

	void ChooseOption(PauseMenuOptions id);
	void DrawMenuButtons();
	void InitMenuButtons();
	void DrawMenuText();

	void ChooseOption(PauseMenuOptions id) {
		switch (id)
		{
		case PauseMenuOptions::RESUME:
			SetPaused(false);
			break;
		case PauseMenuOptions::RESTART:
			InitGame(GetIsMultiplayer(), GetHasPowerups());
			break;
		case PauseMenuOptions::RETURNTOMENU:
			TerminateGame();
			break;
		default:
			std::cout << "Invalid id! [PauseMenu.cpp - ChoosePauseMenuOption()]\n";
			break;
		}
	}

	void DrawMenuButtons() {
		for (int i = 0; i < amountButtons; i++) {
			menuButtons[i].highlighted = (menuCursor == i);
			DrawButton(menuButtons[i]);
		}
	}

	void InitMenuButtons() {
		Button button;
		button.pos.x = GetScreenWidth() * .275;
		button.width = GetScreenWidth() * .45;
		button.height = GetScreenHeight() * .1;
		button.fontSize = button.height * .5;
		button.color = RAYWHITE;
		button.highlighted = false;

		for (int i = 0; i < amountButtons; i++) {
			button.pos.y = (GetScreenHeight() * .4) + (button.height * (i + 1)) + ((button.height * .35) * (i + 1));

			switch ((PauseMenuOptions)i)
			{
			case PauseMenuOptions::RESUME:
				button.text = "Resume";
				break;
			case PauseMenuOptions::RESTART:
				button.text = "RestartGame";
				break;
			case PauseMenuOptions::RETURNTOMENU:
				button.text = "Return to Main Menu";
				break;
			default:
				button.text = "Error";
				std::cout << "Invalid id! [MainMenu.cpp - DrawMainMenuButtons()]\n";
				break;
			}

			menuButtons[i] = button;
		}
	}

	void DrawMenuText() {
		Vector2 pos = { GetScreenWidth() * .5, GetScreenHeight() * .2 };
		DrawCenteredText("GAME PAUSED", pos, GetScreenHeight() * .15, RAYWHITE);
	}

	void DrawMenu() {
		DrawMenuText();
		DrawMenuButtons();
	}

	void MenuInput() {
		UpdateMenuInput(menuCursor, (int)PauseMenuOptions::RESUME, (int)PauseMenuOptions::RETURNTOMENU);

		if (IsKeyPressed(KEY_ENTER)) {
			ChooseOption((PauseMenuOptions)menuCursor);
		}
	}

	void InitMenu() {
		InitMenuButtons();
		menuCursor = 0;
	}
}