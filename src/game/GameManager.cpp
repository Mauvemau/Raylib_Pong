#include "GameManager.h"
#include "raylib.h" // Para tener control de la ventana.
#include "menu/MainMenu.h" // Para tener control de el loop de Main Menu y poder inicializarlo al lanzar el juego.
#include "Game.h" // Para tener control del Loop del Pong.
#include "menu/GameOverMenu.h" // Para tener control del Loop de otros menues.
#include "menu/SettingsMenu.h"
#include "menu/GamemodeMenu.h"
#include <iostream> // Para los errores de consola.

const int screenHeight = 480;
const int screenWidth = 640;

GameStatus gameStatus; // El estado actual del juego.
bool gameShouldClose; // Para salir del game loop.

void InitRespectiveStatus(GameStatus status); // Inicializa una pantalla.
void CloseGame();
void GameLoop();
void InitGameManager();

void InitRespectiveStatus(GameStatus status) {
	switch (status)
	{
	case GameStatus::MAINMENU:
		MainMenu::InitMenu();
		break;
	case GameStatus::SETTINGS:
		Settings::InitMenu();
		break;
	case GameStatus::GAMEMODE:
		GamemodeMenu::InitMenu();
		break;
	case GameStatus::INGAME:
		// Depends on launch settings
		break;
	case GameStatus::GAMEOVERMENU:
		GameOverMenu::InitMenu();
		break;
	default:
		std::cout << "Hope you're in a good mood, you'll need it! [GameManager.cpp - InitRespectiveStatus()]\n";
		break;
	}
}

void SetGameShouldClose(bool value) {
	gameShouldClose = value;
}

void CloseGame() {
	CloseWindow();
}

GameStatus GetGameStatus() {
	return gameStatus;
}

void SetGameStatus(GameStatus status) {
	InitRespectiveStatus(status);
	gameStatus = status;
}

void GameLoop() {
	while (!WindowShouldClose() && !gameShouldClose) {
		switch (gameStatus)
		{
		case GameStatus::MAINMENU:
			MainMenu::MenuLoop();
			break;
		case GameStatus::SETTINGS:
			Settings::MenuLoop();
			break;
		case GameStatus::GAMEMODE:
			GamemodeMenu::MenuLoop();
			break;
		case GameStatus::INGAME:
			PongLoop();
			break;
		case GameStatus::GAMEOVERMENU:
			GameOverMenu::MenuLoop();
			break;
		default:
			std::cout << "Invalid Game Status! [GameManager.cpp - UpdateGameManager()]\n";
			break;
		}
	}
}

void InitGameManager() {
	if (!IsWindowReady()) {
		// SetConfigFlags(FLAG_WINDOW_RESIZABLE); // NOPE, no descomentar, no cambiar las dimensiones de la ventana en medio de una partida.
		InitWindow(screenWidth, screenHeight, "Pong remade for the 285427th time 50 years later");
		SetExitKey(KEY_NULL);
	}
	SetGameStatus(GameStatus::MAINMENU);
	Settings::ResetSettings(); // Se inicializa una unica vez.
}

void RunGame() {
	InitGameManager();
	GameLoop();
	CloseGame();
}