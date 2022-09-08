#pragma once

enum class GameStatus {
	MAINMENU,
	SETTINGS,
	GAMEMODE,
	INGAME,
	GAMEOVERMENU
};

void SetGameShouldClose(bool value);
GameStatus GetGameStatus();
void SetGameStatus(GameStatus status);
void RunGame();