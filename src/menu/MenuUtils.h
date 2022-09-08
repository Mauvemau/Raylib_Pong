#pragma once
#include "raylib.h"

struct Button {
	Vector2 pos;
	float width;
	float height;
	bool highlighted; // Si el boton esta seleccionado.
	Color color;
	const char* text; // Texto el cual mostrar en el centro. (Puede salirse del tamaño del boton.)
	int fontSize; // Tamaño de la font del texto.
};

void DrawCenteredText(const char* text, Vector2 pos, int fontSize, Color color); // Dibuja un texto centrado en una posicion.
void DrawButton(Button button); // Dibuja un botón desde un preset.
void DrawButton(Vector2 pos, float width, float height, bool highlighted, Color color); // Dibuja un boton sin texto.
void DrawButton(Vector2 pos, float width, float height, bool highlighted, Color color, const char* text, int fontSize); // Dibuja un boton con texto.
void UpdateMenuInput(int& cursor, int min, int max); // Registrador de imput para menues, mueve el cursor. (Solo para menues unidimensionales).