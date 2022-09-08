#include "Hud.h"
#include "menu/MenuUtils.h" // Para el texto centrado.
#include "Game.h" // Para los getters de valores.

void DrawActivePowerUps();
void DrawTimer();
void DrawHaltCountdown();
void DrawHudScores();

void DrawActivePowerUps() {
	if (IsThereBonusBall()) {
		Vector2 pos = { GetScreenWidth() * .75, GetScreenHeight() * .92 };
		DrawCenteredText("Bonus Ball!", pos, GetScreenHeight() * .06, ORANGE);
	}
	if (IsThereFrenzy()) {
		Vector2 pos = { GetScreenWidth() * .27, GetScreenHeight() * .92 };
		DrawCenteredText("Frenzy!", pos, GetScreenHeight() * .06, RED);
	}
}

void DrawTimer() {
	Color color;
	int timeLeft = (GetGameTimeLimit() - GetGameTime());
	Vector2 pos = { GetScreenWidth() * .5, GetScreenHeight() * .08 };
	if (timeLeft <= 30 && timeLeft > 20) {
		color = YELLOW;
	}
	else if (timeLeft <= 20 && timeLeft > 10) {
		color = ORANGE;
	}
	else if (timeLeft <= 10) {
		color = RED;
	}
	else {
		color = WHITE;
	}
	DrawCenteredText(TextFormat("%i", timeLeft), pos, GetScreenHeight() * .08, color);
}

void DrawHaltCountdown() {
	int countdown = (GetHaltTime() - GetGameTime());
	Vector2 pos = { GetScreenWidth() * .5, GetScreenHeight() * .94 };
	DrawCenteredText(TextFormat("%i", countdown), pos, GetScreenHeight() * .08, WHITE);
}

void DrawHudScores() {
	DrawText(TextFormat("%i", GetPoints(Direction::LEFT)), GetScreenWidth() * .25, GetScreenHeight() * .2, GetScreenHeight() * .1, BLUE);
	DrawText(TextFormat("%i", GetPoints(Direction::RIGHT)), GetScreenWidth() * .7, GetScreenHeight() * .2, GetScreenHeight() * .1, RED);
}

void DrawHud() {
	if (GetIsHalted()) { // Si esta detenido, mostrar el puntaje.
		DrawHudScores();
		DrawHaltCountdown();
	}
	else {
		DrawTimer();
		DrawActivePowerUps();
	}
}