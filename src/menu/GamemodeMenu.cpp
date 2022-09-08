#include "GamemodeMenu.h"
#include "game/GameManager.h" // Para cambiar el estado a main menu.
#include "game/Game.h" // Para inicializar el juego.
#include <iostream>

namespace GamemodeMenu {

	const int amountButtons = (int)GamemodeMenuOptions::COUNT;
	Button menuButtons[amountButtons];
	int menuCursor;

	bool powerups; // Si estan habilitados los powerups o no.

	void ChooseOption(GamemodeMenuOptions id);
	void DrawMenuButtons();
	void InitMenuButtons();
	void DrawText();
	void DrawMenu();
	void MenuInput();

	void ChooseOption(GamemodeMenuOptions id) {
		switch (id)
		{
		case GamemodeMenuOptions::SINGLEPLAYER:
			InitGame(false, powerups);
			SetGameStatus(GameStatus::INGAME);
			break;
		case GamemodeMenuOptions::MULTIPLAYER:
			InitGame(true, powerups);
			SetGameStatus(GameStatus::INGAME);
			break;
		case GamemodeMenuOptions::TOGGLEPOWERUPS:
			powerups = !powerups;
			break;
		case GamemodeMenuOptions::RETURNTOMENU:
			SetGameStatus(GameStatus::MAINMENU);
			break;
		default:
			break;
		}
	}

	void DrawMenuButtons() {
		for (int i = 0; i < amountButtons; i++) {
			if (i == (int)GamemodeMenuOptions::TOGGLEPOWERUPS && powerups) {
				menuButtons[i].text = "PowerUps ON";
				menuButtons[i].color = GREEN;
			}
			else if (i == (int)GamemodeMenuOptions::TOGGLEPOWERUPS && !powerups) {
				menuButtons[i].text = "PowerUps OFF";
				menuButtons[i].color = RED;
			}
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
			button.pos.y = (GetScreenHeight() * .2) + (button.height * (i + 1)) + ((button.height * .5) * (i + 1));

			switch ((GamemodeMenuOptions)i)
			{
			case GamemodeMenuOptions::SINGLEPLAYER:
				button.text = "Singleplayer";
				break;
			case GamemodeMenuOptions::MULTIPLAYER:
				button.text = "Multiplayer";
				break;
			case GamemodeMenuOptions::TOGGLEPOWERUPS:
				button.text = "PowerUps ON";
				break;
			case GamemodeMenuOptions::RETURNTOMENU:
				button.text = "Return to Main Menu";
				break;
			default:
				button.text = "Error";
				std::cout << "Invalid id! [GamemodeMenu.cpp - InitGamemodeMenuButtons()]\n";
				break;
			}

			menuButtons[i] = button;
		}
	}

	void DrawText() {
		Vector2 pos = { GetScreenWidth() * .5, GetScreenHeight() * .2 };
		DrawCenteredText("Select a Gamemode", pos, GetScreenHeight() * .07, WHITE);
		switch ((GamemodeMenuOptions)menuCursor)
		{
		case GamemodeMenuOptions::SINGLEPLAYER:
			pos = { (float)(GetScreenWidth() * .15), (float)(GetScreenHeight() * .4) };
			DrawCenteredText("Player 1", pos, GetScreenHeight() * .05, BLUE);
			pos = { (float)(GetScreenWidth() * .15), (float)(GetScreenHeight() * .45) };
			DrawCenteredText("A S keys", pos, GetScreenHeight() * .03, WHITE);
			pos = { (float)(GetScreenWidth() * .85), (float)(GetScreenHeight() * .4) };
			DrawCenteredText("CPU", pos, GetScreenHeight() * .05, RED);
			break;
		case GamemodeMenuOptions::MULTIPLAYER:
			pos = { (float)(GetScreenWidth() * .15), (float)(GetScreenHeight() * .55) };
			DrawCenteredText("Player 1", pos, GetScreenHeight() * .05, BLUE);
			pos = { (float)(GetScreenWidth() * .15), (float)(GetScreenHeight() * .6) };
			DrawCenteredText("A S keys", pos, GetScreenHeight() * .03, WHITE);
			pos = { (float)(GetScreenWidth() * .85), (float)(GetScreenHeight() * .6) };
			DrawCenteredText("UP DOWN keys", pos, GetScreenHeight() * .03, WHITE);
			pos = { (float)(GetScreenWidth() * .85), (float)(GetScreenHeight() * .55) };
			DrawCenteredText("Player 2", pos, GetScreenHeight() * .05, RED);
			break;
		default:
			break;
		}
	}

	void DrawMenu() {
		BeginDrawing();
		ClearBackground(BLACK);

		DrawText();
		DrawMenuButtons();

		EndDrawing();
	}

	void MenuInput() {
		UpdateMenuInput(menuCursor, (int)GamemodeMenuOptions::SINGLEPLAYER, (int)GamemodeMenuOptions::RETURNTOMENU);

		if (IsKeyPressed(KEY_ENTER)) {
			ChooseOption((GamemodeMenuOptions)menuCursor);
		}
		else if (IsKeyPressed(KEY_ESCAPE)) {
			SetGameStatus(GameStatus::MAINMENU);
		}
	}

	void MenuLoop() {
		MenuInput();
		DrawMenu();
	}

	void InitMenu() {
		InitMenuButtons();
		menuCursor = 0;
		powerups = true;
	}
}