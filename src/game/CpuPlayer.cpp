#include "CpuPlayer.h"
#include "Game.h"

void GoFetch(Player& player, Ball ball); // Mueve la paleta para arriba o abajo dependiendo la posicion en Y de la pelota.
void CPUJudgeBestTarget(Player& player, Ball ball, Ball bonusBall); // Siempre prioriza la pelota que este mas cerca en X si hay mas de una en rango.

void GoFetch(Player& player, Ball ball) {
	if (ball.pos.y < (player.pos.y + player.tall * .5)) {
		MovePlayer(player, Direction::UP);
		player.dir = Direction::UP;
	}
	else {
		MovePlayer(player, Direction::DOWN);
		player.dir = Direction::DOWN;
	}
}

void CPUJudgeBestTarget(Player& player, Ball ball, Ball bonusBall) { // Originalmente esta funcion era con return, pero se producian crashes si la resolucion era ultrawide.
	if (ball.ax.y == Direction::RIGHT && bonusBall.ax.y == Direction::RIGHT) {
		if (ball.pos.x > bonusBall.pos.x) {
			GoFetch(player, ball);
		}
		else {
			GoFetch(player, bonusBall);
		}
	}
	else if (ball.ax.y == Direction::RIGHT){
		GoFetch(player, ball);
	}
	else if (bonusBall.ax.y == Direction::RIGHT) {
		GoFetch(player, bonusBall);
	}
}

void UpdateCPUPlayer(Player& player, Ball ball, Ball bonusBall) {
	if (ball.pos.x > (GetScreenWidth() * .5) && bonusBall.pos.x > (GetScreenWidth() * .5)) {
		CPUJudgeBestTarget(player, ball, bonusBall);
	}
	else if (ball.pos.x > GetScreenWidth() * .5 && ball.ax.y == Direction::RIGHT) { // Si la pelota esta en rango.
		GoFetch(player, ball);
	}
	else if (bonusBall.pos.x > GetScreenWidth() * .5 && bonusBall.ax.y == Direction::RIGHT) {
		GoFetch(player, bonusBall);
	}
}