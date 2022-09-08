#pragma once
#include "raylib.h"
#include "Player.h" // Para colisiones
#include "Speedbump.h" // Para checkear colision con los bumps

struct Ball { // Struct de la pelota.
    float radius;
    Vector2 pos;
    Color color;
    float baseSpeed;
    float currentSpeed;
    float horizontalSpeed;
    float verticalSpeed;
    Axis ax; // La direccion a la cual mover esta pelota.
    float cooldown; // En cuantos segundos la pelota puede aumentar nuevamente su velocidad.
    bool bonus; // Si es una pelota bonus. (Parte de los powerup)
};

void FrenzyBall(Ball& ball);
void DespawnBonusBall(Ball& ball); // Para despawnear las pelotas bonus.
void UpdateBall(Ball& ball, Player player1, Player player2, Bumps& bumps); // Maneja la logica de la pelota.
void DrawBall(Ball ball); // Dibuja la pelota
void InitBonusBall(Ball& ball); // Crea una pelota bonus, que tiene una logica diferente a la comun.
void InitBall(Ball& ball); // Maneja el inicializado de la pelota.