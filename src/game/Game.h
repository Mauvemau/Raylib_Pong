#pragma once
#include "GameUtils.h"

bool GetHasPowerups(); // Devielve si los powerups estan activados o no.
bool GetIsMultiplayer(); // Devuelve si el juego esta en multiplayer o no. (En caso de usarse el boton de volver a jugar.)
void StopFrenzy(); // Frena frenzy mode.
void StartFrenzy(); // Inicia frenzy mode.
bool IsThereFrenzy(); // Si frenzy esta activo.
void StopBonusBall(); // Hacer que la logica de la bonus ball pare.
void SpawnBonusBall(); // Spawnear una pelota bonus.
bool IsThereBonusBall(); // Si actualmente hay una pelota bonus spawneada.
int GetGameTimeLimit(); // Devuelve el tiempo limite de la partida.
int GetGameTime(); // Devuelve la cantidad de segundos transcurridos (Sin pausa) desde el comienzo de la partida.
void TerminateGame(); // Se vuelve directo al menu.
void FinishGame(); // Se ocupa de lanzar la pantalla de Game Over al darse la condicion de fin de juego.
int GetPoints(Direction side); // Devuelve el puntaje del jugador de respectivo lado. Lo hice de esta forma por que Hud no tiene referencia a los players.
void AddPoints(Direction side); // Añade puntos a el jugador de respectivo lado.
// "Detenido" es cuando la pelota sola se encuentra congelada, "Pausado" es cuando el juego entero esta pausado.
bool GetIsHalted(); // Devuelve si el juego esta detenido o no.
int GetHaltTime(); // (Para el Hud) Devuelve cuando la pelota comenzara a moverse.
void HaltGame(); // Pausa el movimiento de la pelota por unos segundos.
bool GetIsPaused(); // Devuelve si el juego esta pausado o no.
void SetPaused(bool value); // Setea si el juego esta pausado a un valor.
void PongLoop(); // Llama a input, update y draw en cada iteración.
void InitGame(bool setMultiplayer, bool setPowerups); // Inicializa las variables del juego, llama funciones de inicializacion.