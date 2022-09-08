#include "GameOverMenu.h"
#include "game/GameManager.h" // Para cambiar el estado a juego si se quiere volver a jugar, o a main menu si se quiere volver al menu.
#include "game/Game.h" // Inicializar el juego otra vez si se quiere volver a jugar.
#include <iostream> // Para los errores de consola.

namespace GameOverMenu {

	const int amountButtons = (int)GameOverMenuOptions::COUNT;
	Button menuButtons[amountButtons];
	int menuCursor;

	void DrawMenuButtons();
	void InitMenuButtons();
	void ChooseOption(GameOverMenuOptions id);
	void DrawThankMessage(); // Dibuja un texto abajo de los botones.
	void DrawScores(); // Dibuja los puntajes de cada jugador.
	void DrawWinnerMessage(); // Dibuja un texto mostrando quien ganó.
	void DrawMenu();
	void MenuInput();

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
			button.pos.y = (GetScreenHeight() * .4) + (button.height * (i + 1)) + ((button.height * .4) * (i + 1));

			switch ((GameOverMenuOptions)i)
			{
			case GameOverMenuOptions::PLAYAGAIN:
				button.text = "Play Again";
				break;
			case GameOverMenuOptions::RETURNTOMENU:
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

	void ChooseOption(GameOverMenuOptions id) {
		switch (id)
		{
		case GameOverMenuOptions::PLAYAGAIN:
			InitGame(GetIsMultiplayer(), GetHasPowerups());
			SetGameStatus(GameStatus::INGAME);
			break;
		case GameOverMenuOptions::RETURNTOMENU:
			SetGameStatus(GameStatus::MAINMENU);
			break;
		default:
			std::cout << "Invalid id! [GameOverMenu.cpp - ChooseGameOverMenuOption()]\n";
			break;
		}
	}

	void DrawThankMessage() {
		Vector2 pos = { (float)(GetScreenWidth() * .5), (float)(GetScreenHeight() * .97) };
		DrawCenteredText("Thank you for playing!", pos, GetScreenHeight() * .035, WHITE);
	}

	void DrawScores() {
		int player1Points = GetPoints(Direction::LEFT);
		int player2Points = GetPoints(Direction::RIGHT);

		Vector2 pos = { (float)(GetScreenWidth() * .25), (float)(GetScreenHeight() * .35) };
		DrawCenteredText(TextFormat("%i", player1Points), pos, GetScreenHeight() * .2, BLUE);

		pos = { (float)(GetScreenWidth() * .5), (float)(GetScreenHeight() * .35) };
		DrawCenteredText("vs", pos, GetScreenHeight() * .1, RAYWHITE);

		pos = { (float)(GetScreenWidth() * .75), (float)(GetScreenHeight() * .35) };
		DrawCenteredText(TextFormat("%i", player2Points), pos, GetScreenHeight() * .2, RED);

	}

	void DrawWinnerMessage() {
		int player1Points = GetPoints(Direction::LEFT);
		int player2Points = GetPoints(Direction::RIGHT);
		Vector2 pos = { GetScreenWidth() * .5, GetScreenHeight() * .15 };
		if (player1Points == player2Points) {
			DrawCenteredText("It's a Tie!", pos, GetScreenHeight() * .09, RAYWHITE);
		}
		else if (player1Points > player2Points) {
			DrawCenteredText("Player 1 Wins!", pos, GetScreenHeight() * .09, SKYBLUE);
		}
		else {
			DrawCenteredText("Player 2 Wins!", pos, GetScreenHeight() * .09, RED);
		}
	}

	void DrawMenu() {
		BeginDrawing();
		ClearBackground(BLACK);

		DrawWinnerMessage();
		DrawScores();
		DrawMenuButtons();
		DrawThankMessage();

		EndDrawing();
	}

	void MenuInput() {
		UpdateMenuInput(menuCursor, (int)GameOverMenuOptions::PLAYAGAIN, (int)GameOverMenuOptions::RETURNTOMENU);

		if (IsKeyPressed(KEY_ENTER)) {
			ChooseOption((GameOverMenuOptions)menuCursor);
		}
	}

	void MenuLoop() {
		MenuInput();
		DrawMenu();
	}

	void InitMenu() {
		InitMenuButtons();
		menuCursor = 1;
	}
}