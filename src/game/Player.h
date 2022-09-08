#pragma once
#include "raylib.h" 
#include "GameUtils.h"

struct Player { // Struct de jugador.
    float tall;
    float wide;
    Vector2 pos;
    Color color;
    float speed;
    Direction dir; // Direccion a la cual se esta moviendo.
    int points; // Puntaje.
};

void AddPoints(Player& ply, int points); // Añade una cantidad de puntos a respectivo player.
void ResetPlayer(Player& ply); // Reinicia el jugador al centro de la pantalla.
void MovePlayer(Player& ply, Direction dir); // Mueve a un jugador hacia 2 diferentes direcciones, limitado por el tamaño de la pantalla.
void TeleportPlayer(Player& ply, Vector2 pos); // Teletransporta a un jugador a una posicion en pantalla.
void DrawPlayer(Player ply); // Dibuja a un jugador en pantalla.
void InitPlayers(Player& player1, Player& player2); // Maneja el inicializado de los jugadores.