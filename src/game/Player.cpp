#include "Player.h"

Vector2 GetCenter(Player ply); // Recibe un jugador, devuelve el pivot central de ese jugador.
Player CreatePlayer(Color color); // Crea un jugador default.

void AddPoints(Player& ply, int points) {
	ply.points += points;
}

void ResetPlayer(Player& ply) {
	ply.pos.y = GetScreenHeight() * .5;
}

void MovePlayer(Player& ply, Direction dir) {
	switch (dir)
	{
	case Direction::UP:
		if (ply.pos.y > 0) {
			ply.pos.y -= ply.speed * GetFrameTime();
		}
		else {
			ply.pos.y = 0;
		}
		break;
	case Direction::DOWN:
		if (ply.pos.y + ply.tall < GetScreenHeight()) {
			ply.pos.y += ply.speed * GetFrameTime();
		}
		else {
			ply.pos.y = GetScreenHeight() - ply.tall;
		}
		break;
	default:
		break;
	}
}

void TeleportPlayer(Player& ply, Vector2 pos) {
	Vector2 middle;

	middle = GetCenter(ply);

	ply.pos = { pos.x - middle.x, pos.y - middle.y };
}

void DrawPlayer(Player ply) {
	DrawRectangle(ply.pos.x, ply.pos.y, ply.wide, ply.tall, ply.color);
}

Vector2 GetCenter(Player ply) {
	Vector2 center;

	center = { ply.wide / 2,  ply.tall / 2 };

	return center;
}

Player CreatePlayer(Color color) {
	Player ply;

	ply.tall = (float)(GetScreenHeight() * .2);
	ply.wide = (float)(GetScreenWidth() * .02);
	ply.color = color;
	ply.speed = GetScreenHeight() * .8; // La velocidad del jugador depende del alto de la pantalla.
	ply.dir = Direction::STILL;
	ply.points = 0;

	return ply;
}

void InitPlayers(Player& player1, Player& player2) {
	Vector2 pos;
	player1 = CreatePlayer(BLUE);
	pos = { (float)(GetScreenWidth() * .1), (float)(GetScreenHeight() * .5) };
	TeleportPlayer(player1, pos);
	player2 = CreatePlayer(RED);
	pos = { (float)(GetScreenWidth() * .9), (float)(GetScreenHeight() * .5) };
	TeleportPlayer(player2, pos);
}