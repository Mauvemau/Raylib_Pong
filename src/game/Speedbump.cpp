#include "Speedbump.h"
#include "Game.h";
#include "menu/MenuUtils.h" // Para el texto centrado.
#include <iostream>

const int powerupCooldown = 30;
int nextPowerupSpawn;

void GiveRandomPower(Speedbump& bump);
void DrawSpeedbump(Speedbump bump);
void SpeedbumpLogic(Bumps& bumps);
Bumps CreateBumps();

void SetPowerUpActive(Power power) {
	if (IsThereBonusBall()) {
		StartFrenzy();
	}
	else if (IsThereFrenzy()) {
		SpawnBonusBall();
	}
	else {
		switch (power)
		{
		case Power::BONUSBALL:
			SpawnBonusBall();
			break;
		case Power::FRENZY:
			StartFrenzy();
			break;
		default:
			std::cout << "Invalid power! Speedbump.cpp - SetPowerUpActive()\n";
			break;
		}
	}
}

bool IsSpeedbumpActive(Speedbump bump) {
	return bump.power != Power::EMPTY;
}

void RemovePower(Speedbump& bump) {
	bump.power = Power::EMPTY;
}

void GiveRandomPower(Speedbump& bump) {
	bump.power = (Power)GetRandomValue((int)Power::BONUSBALL, (int)Power::FRENZY);
}

void DrawSpeedbump(Speedbump bump) {
	if (bump.power != Power::EMPTY) {
		DrawRectangle(bump.pos.x, bump.pos.y, bump.wide, bump.tall, ORANGE);
		Vector2 pos = { (float)(bump.pos.x - (float)(GetScreenWidth() * .03)), bump.pos.y + (bump.tall * .5) };
		DrawCenteredText("!", pos, GetScreenHeight() * .05, RED);
		pos = { (float)((bump.pos.x + bump.wide) + (float)(GetScreenWidth() * .03)), (float)(bump.pos.y + (bump.tall * .5)) };
		DrawCenteredText("!", pos, GetScreenHeight() * .05, RED);
	}
	else {
		DrawRectangle(bump.pos.x, bump.pos.y, bump.wide, bump.tall, DARKGRAY);
	}
}

void DrawSpeedbumps(Bumps bumps) {
	DrawSpeedbump(bumps.top);
	DrawSpeedbump(bumps.bottom);
}

void SpeedbumpLogic(Bumps& bumps) {
	if (GetGameTime() > nextPowerupSpawn) {
		int which = GetRandomValue(0, 1);
		if (which) {
			GiveRandomPower(bumps.top);
		}
		else {
			GiveRandomPower(bumps.bottom);
		}

		nextPowerupSpawn = GetGameTime() + powerupCooldown;
	}
}

void UpdateSpeedbumps(Bumps& bumps) {
	SpeedbumpLogic(bumps);
}

Bumps CreateBumps() {

	Speedbump bump;
	bump.wide = GetScreenWidth() * .02;
	bump.tall = GetScreenHeight() * .25;
	bump.power = Power::EMPTY;

	Bumps bumps;
	bumps.top = bump;
	bumps.bottom = bump;

	bumps.top.pos.x = (GetScreenWidth() * .5) - (bumps.top.wide * .5);
	bumps.top.pos.y = (GetScreenHeight() * .25) - (bumps.top.tall * .5);
	bumps.bottom.pos.x = (GetScreenWidth() * .5) - (bumps.bottom.wide * .5);
	bumps.bottom.pos.y = (GetScreenHeight() * .75) - (bumps.bottom.tall * .5);

	return bumps;
}

void InitSpeedbumps(Bumps& bumps) {
	bumps = CreateBumps();
	nextPowerupSpawn = GetGameTime() + powerupCooldown;
}