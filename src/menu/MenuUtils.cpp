#include "MenuUtils.h"
#include "raylib.h"
#include <iostream>

void DrawCenteredText(const char* text, Vector2 pos, int fontSize, Color color) {
	int textWide = MeasureText(text, fontSize);
	DrawText(text, (pos.x) - (textWide * .5), (pos.y) - (fontSize * .5), fontSize, color);
}

void DrawButton(Button button) {
	Vector2 textPos = { button.pos.x + (button.width * .5), button.pos.y + (button.height * .5) };
	if (!button.highlighted) {
		DrawRectangleLines(button.pos.x, button.pos.y, button.width, button.height, button.color);
		DrawCenteredText(button.text, textPos, button.fontSize, button.color);
	}
	else {
		DrawRectangle(button.pos.x, button.pos.y, button.width, button.height, button.color);
		DrawCenteredText(button.text, textPos, button.fontSize, BLACK); // El color de fondo siempre es negro.
	}
}

void DrawButton(Vector2 pos, float width, float height, bool highlighted, Color color) {
	if (!highlighted) {
		DrawRectangleLines(pos.x, pos.y, width, height, color);
	}
	else {
		DrawRectangle(pos.x, pos.y, width, height, color);
	}
}

void DrawButton(Vector2 pos, float width, float height, bool highlighted, Color color, const char* text, int fontSize) {
	Vector2 textPos = { pos.x + (width * .5), pos.y + (height * .5) };
	if (!highlighted) {
		DrawRectangleLines(pos.x, pos.y, width, height, color);
		DrawCenteredText(text, textPos, fontSize, color);
	}
	else {
		DrawRectangle(pos.x, pos.y, width, height, color);
		DrawCenteredText(text, textPos, fontSize, BLACK);
	}
}

void UpdateMenuInput(int& cursor, int min, int max) {
	if (IsKeyPressed(KEY_W)) {
		cursor--;
	}
	else if (IsKeyPressed(KEY_A)) {
		cursor--;
	}
	else if (IsKeyPressed(KEY_S)) {
		cursor++;
	}
	else if (IsKeyPressed(KEY_D)) {
		cursor++;
	}
	else if (IsKeyPressed(KEY_UP)) {
		cursor--;
	}
	else if (IsKeyPressed(KEY_LEFT)) {
		cursor--;
	}
	else if (IsKeyPressed(KEY_DOWN)) {
		cursor++;
	}
	else if (IsKeyPressed(KEY_RIGHT)) {
		cursor++;
	}

	// Rota el cursor.
	if (cursor > max) {
		cursor = min;
	}
	if (cursor < min) {
		cursor = max;
	}
}