#include "MainMenu.h"
#include "game/GameManager.h" // Para cambiar el estado del programa a juego.
#include <iostream> // Para los errores de consola.

namespace MainMenu {

	const int amountButtons = (int)MainMenuOptions::COUNT;
	Button menuButtons[amountButtons]; // Un array con los botones.
	int menuCursor; // Cursor del menu, se ocupa de seleccionar botones.

	bool instructions; // Comienza a dibujar las instrucciones.

	void DrawInstructions();
	void ShowInstructions(bool show);
	void DrawMenuButtons(); // Se ocupa de dibujar los botones del main menu.
	void InitMenuButtons(); // Inicializa los botones del menu.
	void DrawMenuControls(); // Muestra los controles del MainMenu.
	void DrawMenuCredits(); // Dibuja un pequeño texto que muestra los creditos.
	void DrawMenuLogo();
	void ChooseOption(MainMenuOptions id); // Si se elije alguna opcion del menu.
	void DrawMenu();
	void MenuInput();

	void DrawInstructions() {
		Vector2 pos = { GetScreenWidth() * .5, GetScreenHeight() * .1 };
		DrawCenteredText("This Pong works on a \"Ball angle by friction\" type.", pos, GetScreenHeight() * .04, ORANGE);
		pos = { (float)(GetScreenWidth() * .5), (float)(GetScreenHeight() * .2) };
		DrawCenteredText("If the paddle hits the ball while both", pos, GetScreenHeight() * .04, WHITE);
		pos = { (float)(GetScreenWidth() * .5), (float)(GetScreenHeight() * .25) };
		DrawCenteredText("are moving towards the same direction,", pos, GetScreenHeight() * .04, WHITE);
		pos = { (float)(GetScreenWidth() * .5), (float)(GetScreenHeight() * .3) };
		DrawCenteredText("the ball will bounce in a narrow angle.", pos, GetScreenHeight() * .04, WHITE);

		pos = { (float)(GetScreenWidth() * .5), (float)(GetScreenHeight() * .4) };
		DrawCenteredText("Hit it while moving the opposite direction to", pos, GetScreenHeight() * .04, WHITE);
		pos = { (float)(GetScreenWidth() * .5), (float)(GetScreenHeight() * .45) };
		DrawCenteredText("shoot it in a wide angle.", pos, GetScreenHeight() * .04, WHITE);

		pos = { (float)(GetScreenWidth() * .5), (float)(GetScreenHeight() * .55) };
		DrawCenteredText("If you stand still while the ball hits you", pos, GetScreenHeight() * .04, WHITE);
		pos = { (float)(GetScreenWidth() * .5), (float)(GetScreenHeight() * .6) };
		DrawCenteredText("it will bounce in a normal angle.", pos, GetScreenHeight() * .04, WHITE);

		pos = { (float)(GetScreenWidth() * .5), (float)(GetScreenHeight() * .7) };
		DrawCenteredText("Alternatively you can hit the ball with the sides", pos, GetScreenHeight() * .04, WHITE);
		pos = { (float)(GetScreenWidth() * .5), (float)(GetScreenHeight() * .75) };
		DrawCenteredText("of the paddle to change it's direction.", pos, GetScreenHeight() * .04, WHITE);

		pos = { (float)(GetScreenWidth() * .5), (float)(GetScreenHeight() * .9) };
		DrawCenteredText("(Press any key to return to the menu)", pos, GetScreenHeight() * .045, RED);
	}

	void ShowInstructions(bool show) {
		instructions = show;
	}

	void DrawMenuButtons() {
		for (int i = 0; i < amountButtons; i++) {
			menuButtons[i].highlighted = (menuCursor == i);
			DrawButton(menuButtons[i]);
		}
	}

	void InitMenuButtons() {
		Button button;
		button.pos.x = GetScreenWidth() * .35;
		button.width = GetScreenWidth() * .3;
		button.height = GetScreenHeight() * .1;
		button.fontSize = button.height * .5;
		button.color = RAYWHITE;
		button.highlighted = false;

		for (int i = 0; i < amountButtons; i++) {
			button.pos.y = (GetScreenHeight() * .25) + (button.height * (i + 1)) + ((button.height * .35) * (i + 1));

			switch ((MainMenuOptions)i)
			{
			case MainMenuOptions::PLAY:
				button.text = "Play";
				break;
			case MainMenuOptions::HOW2PLAY:
				button.text = "Instructions";
				break;
			case MainMenuOptions::SETTINGS:
				button.text = "Settings";
				break;
			case MainMenuOptions::EXIT:
				button.text = "Exit";
				break;
			default:
				button.text = "Error";
				std::cout << "Invalid id! [MainMenu.cpp - InitMenuButtons]\n";
				break;
			}

			menuButtons[i] = button;
		}
	}

	void DrawMenuControls() {
		Vector2 pos = { GetScreenWidth() * .5, GetScreenHeight() * .32 };
		DrawCenteredText("Use WASD or the Arrow Keys to navigate the menu, ENTER key to confirm", pos, GetScreenHeight() * .035, WHITE);
	}

	void DrawMenuCredits() {
		const char* text = "Game built by Salazar using Raylib by Ray";
		int fontSize = GetScreenHeight() * .03;
		int textWide = MeasureText(text, fontSize);
		DrawText(text, (GetScreenWidth() * .99) - textWide, (GetScreenHeight() * .99) - fontSize, fontSize, WHITE);
	}

	void DrawMenuLogo() {
		Vector2 pos1 = { GetScreenWidth() * .5, GetScreenHeight() * .15 };
		Vector2 pos2 = { GetScreenWidth() * .5, GetScreenHeight() * .21 };
		DrawCenteredText("Pong remade for the 285427th time", pos1, GetScreenHeight() * .07, SKYBLUE);
		DrawCenteredText("50 years later", pos2, GetScreenHeight() * .04, ORANGE);
	}

	void ChooseOption(MainMenuOptions id) {
		switch (id)
		{
		case MainMenuOptions::PLAY:
			SetGameStatus(GameStatus::GAMEMODE);
			break;
		case MainMenuOptions::HOW2PLAY:
			ShowInstructions(true);
			break;
		case MainMenuOptions::SETTINGS:
			SetGameStatus(GameStatus::SETTINGS);
			break;
		case MainMenuOptions::EXIT:
			SetGameShouldClose(true);
			break;
		default:
			std::cout << "Invalid id! [MainMenu.cpp - ChooseOption]\n";
			break;
		}
	}

	void DrawMenu() {
		BeginDrawing();
		ClearBackground(BLACK);

		if (!instructions) {
			DrawMenuLogo();
			DrawMenuCredits();
			DrawMenuControls();
			DrawMenuButtons();
		}
		else {
			DrawInstructions();
		}

		EndDrawing();
	}

	void MenuInput() {
		if (!instructions) {
			UpdateMenuInput(menuCursor, (int)MainMenuOptions::PLAY, (int)MainMenuOptions::EXIT);

			if (IsKeyPressed(KEY_ENTER)) {
				ChooseOption((MainMenuOptions)menuCursor);
			}
		}
		else {
			if (GetKeyPressed()) {
				ShowInstructions(false);
			}
		}
	}

	void MenuLoop() {
		MenuInput();
		DrawMenu();
	}

	void InitMenu() {
		InitMenuButtons();
		menuCursor = 0;
		instructions = false;
	}
}