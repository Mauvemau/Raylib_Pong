#pragma once
#include "raylib.h"

enum class Power {
	BONUSBALL,
	FRENZY,
	EMPTY // Si el speedbump no tiene actualmente ningun powerup.
};

struct Speedbump {
	Vector2 pos;
	float wide;
	float tall;
	Power power;
};

struct Bumps {
	Speedbump top;
	Speedbump bottom;
};

void SetPowerUpActive(Power power);
bool IsSpeedbumpActive(Speedbump bump);
void RemovePower(Speedbump& bump);
void DrawSpeedbumps(Bumps bumps);
void UpdateSpeedbumps(Bumps& bumps);
void InitSpeedbumps(Bumps& bumps);