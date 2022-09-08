#include "Game.h"
#include "GameManager.h" // Para poder alternar de loops si se quiere salir del juego o si el juego finaliza.
#include "Player.h" // Para declarar los players y llamar a sus funciones.
#include "CpuPlayer.h" // Si jugamos contra el cpu.
#include "Ball.h" // Para declarar la pelota y llamar a sus funciones.
#include "Hud.h" // Hud del juego.
#include "menu/PauseMenu.h" // Parecido al hud pero con input.
#include "Speedbump.h" // Para los powerups
#include <iostream> // Para los errores de consola.

// Juego
const int timeLimit = 121; // Cuantos segundos para que termine la partida.
int timer; // Cuenta los segundos de la partida.
int lastTick; // Para la logica del timer.
bool paused; // Si el juego se encuentra pausado.
bool multiplayer; // Si jugamos contra un segundo jugador, o contra la maquina.

// Powerups
bool powerups;
Bumps bumps;
bool isBonusBallSpawned; // Si la pelota bonus esta actualmente activa.
bool isFrenzyActive;

// Jugadores
Player player1;
Player player2;

// Ball
Ball ball;
Ball bonusBall;
const int haltTime = 3; // Cantidad de segundos que el juego se detiene antes de comenzar a mover la pelota.
int haltResumes; // El tiempo en el cual la pelota puede comenzar a moverse nuevamente.

void CheckFinishCondition(); // Checkea si se dan las condiciones para que la partida termine.
void TickTime(); // Avanza el timer de la partida. (Este timer no avanza cuando el juego se encuentra pausado.)
void TogglePause(); // Pone el juego en pausa on/off.
void DrawGame(); // Dibuja los objetos en pantalla.
void GameUpdate(); // Llama a funciones de update.
void CheckInput(); // Checkea input del usuario.

bool GetHasPowerups() {
	return powerups;
}

bool GetIsMultiplayer() {
	return multiplayer;
}

void StopFrenzy() {
	isFrenzyActive = false;
}

void StartFrenzy() {
	FrenzyBall(ball);
	isFrenzyActive = true;
}

bool IsThereFrenzy() {
	return isFrenzyActive;
}

void StopBonusBall() {
	isBonusBallSpawned = false;
}

void SpawnBonusBall() {
	InitBonusBall(bonusBall);
	isBonusBallSpawned = true;
}

bool IsThereBonusBall() {
	return isBonusBallSpawned;
}

void CheckFinishCondition() {
	if (timer >= timeLimit) {
		FinishGame();
	}
}

int GetGameTimeLimit() {
	return timeLimit;
}

int GetGameTime() {
	return timer;
}

void TickTime() {
	if (!paused) { // Si el juego no esta pausado, hacer que el timer avanze
		if (GetTime() > lastTick) {
			timer++;
			lastTick = GetTime() + 1;
		}
		CheckFinishCondition();
	}
}

void TerminateGame() {
	std::cout << "Terminating game...\n";
	SetGameStatus(GameStatus::MAINMENU);
}

void FinishGame() {
	std::cout << "Finishing game...\n";
	SetGameStatus(GameStatus::GAMEOVERMENU);
}

int GetPoints(Direction side) {
	int points = 0;
	switch (side)
	{
	case Direction::LEFT:
		points = player1.points;
		break;
	case Direction::RIGHT:
		points = player2.points;
		break;
	default:
		points = 404;
		std::cout << "Invalid side! [Game.cpp - GetPoints()]\n";
		break;
	}
	return points;
}

void AddPoints(Direction side) {
	switch (side)
	{
	case Direction::LEFT:
		AddPoints(player1, 1);
		break;
	case Direction::RIGHT:
		AddPoints(player2, 1);
		break;
	default:
		std::cout << "Invalid side! [Game.cpp - AddPoints()]\n";
		break;
	}
}

bool GetIsHalted() {
	return (GetGameTime() < haltResumes);
}

int GetHaltTime() {
	return haltResumes;
}

void HaltGame() {
	haltResumes = GetGameTime() + haltTime;
}

bool GetIsPaused() {
	return paused;
}

void SetPaused(bool value) {
	paused = value;
}

void TogglePause() {
	paused = !paused;
}

void DrawGame() {
	BeginDrawing();
	ClearBackground(BLACK);

	if (powerups) {
		DrawSpeedbumps(bumps);
	}

	DrawBall(ball);
	if (isBonusBallSpawned) { // Dibujar la bonus ball si esta spawneada.
		DrawBall(bonusBall);
	}
	DrawPlayer(player1);
	DrawPlayer(player2);

	if (!paused) {
		DrawHud();
	}
	else { // Dibujar el menu de pausa si el juego esta pausado.
		PauseMenu::DrawMenu();
	}

	EndDrawing();
}

void GameUpdate() {
	TickTime();
	if (!GetIsHalted()) { // Si el juego esta detenido, no updatear la pelota.
		UpdateBall(ball, player1, player2, bumps);
		if (isBonusBallSpawned) { // Updatear la bonus ball si esta spawneada.
			UpdateBall(bonusBall, player1, player2, bumps);
		}
	}
	if (powerups) {
		UpdateSpeedbumps(bumps);
	}
}

void CheckInput() {
	if (IsKeyPressed(KEY_ESCAPE)) {
		TogglePause();
	}

	if (!paused) { // No permitir contolar jugadores si el juego se encuentra pausado.
		if (IsKeyDown(KEY_W)) {
			MovePlayer(player1, Direction::UP);
			player1.dir = Direction::UP;
		}
		else if (IsKeyDown(KEY_S)) {
			MovePlayer(player1, Direction::DOWN);
			player1.dir = Direction::DOWN;
		}
		else {
			player1.dir = Direction::STILL;
		}
		if (multiplayer) {
			if (IsKeyDown(KEY_UP)) {
				MovePlayer(player2, Direction::UP);
				player2.dir = Direction::UP;
			}
			else if (IsKeyDown(KEY_DOWN)) {
				MovePlayer(player2, Direction::DOWN);
				player2.dir = Direction::DOWN;
			}
			else {
				player2.dir = Direction::STILL;
			}
		}
	}
#ifdef _DEBUG
	if(IsKeyPressed(KEY_F3)) {
		TerminateGame();
	}
	if (IsKeyPressed(KEY_F4)) {
		FinishGame();
	}
#endif // _DEBUG
}

void PongLoop() {
	CheckInput();
	if (!paused) {
		GameUpdate();
		if (!multiplayer) {
			UpdateCPUPlayer(player2, ball, bonusBall);
		}
	}
	else {
		PauseMenu::MenuInput();
	}
	DrawGame();
}

void InitGame(bool setMultiplayer, bool setPowerups) {
	// Variables
	timer = 0;
	lastTick = GetTime();
	paused = false;
	multiplayer = setMultiplayer;
	powerups = setPowerups;
	PauseMenu::InitMenu();

	// Powerups
	isBonusBallSpawned = false;
	isFrenzyActive = false;
	if (powerups) {
		InitSpeedbumps(bumps);
	}

	// Jugadores
	InitPlayers(player1, player2);

	// Pelota
	haltResumes = 0;
	InitBall(ball);
	InitBonusBall(bonusBall);
}