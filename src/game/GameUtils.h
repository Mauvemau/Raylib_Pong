#pragma once

/*
Este header es para enums/structs/funciones generales que tienen distintas utilidades en varios ambitos diferentes.
(En realidad arme este struct por que se me estaba haciendo un spaghetti de #includes al tener esos enums puestos 
en archivos diferentes.
Mas tarde hize lo mismo con los menues por que me resultó mas comodo.)
*/

enum class Direction { // Enum de posibles direcciones para mover objetos en pantalla.
	UP,
	DOWN,
	LEFT,
	RIGHT,
	STILL // Ninguna direccion.
};

struct Axis { // Para direcciones diagonales.
	Direction x;
	Direction y;
};

enum class Angle { // Enum de posibles angulos de la pelota.
	NORMAL,
	WIDE,
	NARROW,
	COUNT // The amount of values.
};