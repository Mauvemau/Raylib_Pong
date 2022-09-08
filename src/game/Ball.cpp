#include "Ball.h"
#include "Game.h" // Para poder detener el juego.
#include <iostream> // Para los errores de consola y logs de testeo.

const float speedInterval = 3.0f; // Cada cuantos segundos se aumenta la velocidad.
const float speedIncrease = 1.1; // Cuanto es el aumento en velocidad.

void Unfrenzy(Ball& ball);
void BallSpeedbumpCollision(Speedbump& bump, Ball ball);
void RandomizeAngle(Ball& ball); // Randomiza el angulo de la pelota.
void SetAngle(Ball& ball, Angle ang); // Recibe un enum Angle, cambia el angulo de la pelota.
void ResetBall(Ball& ball, Direction dir); // Reinicia la pelota hacia una direccion horizontal especifica, puede salir desde posiciones diferentes con angulos aleatorios.
void ResetBallRandom(Ball& ball); // Reinicia la pelota hacia una direccion random.
void BallDirectionManager(Ball& ball, Player ply); // Calcula la direccion de la pelota dependiendo que parte de la paleta choca. -----
void HalveBallSpeed(Ball& ball); // Corta la velocidad de la pelota por la mitad.
void IncreaseBallSpeed(Ball& ball); // Aumenta la velocidad de la pelota, si se puede.
void BallSpeedManager(Ball& ball, Player ply); // Cambia la velocidad vertical de la pelota dependiendo de la direccion hacia la que la paleta se esta moviendo. ----
void BallBehaviourManager(Ball& ball, Player ply); // Maneja la reaccion de la pelota al chocar contra una paleta.
void SwitchDirection(Ball ball, Direction& dir); // Cambia una direccion dependiendo de donde se encuentra la pelota.
void BallPlayerCollision(Player ply, Ball& ball); // Maneja la colision de la pelota con los jugadores.
void BallWallCollision(Ball& ball); // Maneja la colision de la pelota con las paredes del nivel.
void MoveBall(Ball& ball, Direction dir, float speed);  // Mueve la pelota hacia una direccion; Puede llamarse 2 veces para mover la pelota en diagonal.
Ball CreateBall(Color color); // Crea una pelota default.

void Unfrenzy(Ball& ball) {
    StopFrenzy();
    ball.radius = ball.radius * .25;
    HalveBallSpeed(ball);
}

void FrenzyBall(Ball& ball) {
    ball.radius = ball.radius * 4;
    ball.currentSpeed = ball.currentSpeed * 2;
}

void BallSpeedbumpCollision(Speedbump& bump, Ball ball) {
    if (bump.pos.x < ball.pos.x + ball.radius &&
        bump.pos.x + bump.wide > ball.pos.x - ball.radius &&
        bump.pos.y < ball.pos.y + ball.radius &&
        bump.tall + bump.pos.y > ball.pos.y - ball.radius) {
        SetPowerUpActive(bump.power);
        RemovePower(bump);
    }
}

void DespawnBonusBall(Ball& ball) {
    StopBonusBall();
}

void RandomizeAngle(Ball& ball) {
    int value = GetRandomValue((int)(Angle::NORMAL), (int)(Angle::COUNT) - 1);
    Angle ang = (Angle)value;
    SetAngle(ball, ang);
}

void SetAngle(Ball& ball, Angle ang) {
    switch (ang)
    {
    case Angle::NORMAL:
        ball.verticalSpeed = ball.currentSpeed;
        ball.horizontalSpeed = ball.currentSpeed;
        break;
    case Angle::WIDE:
        ball.verticalSpeed = (float)(ball.currentSpeed * .75);
        ball.horizontalSpeed = (float)(ball.currentSpeed * 1.25);
        break;
    case Angle::NARROW:
        ball.verticalSpeed = (float)(ball.currentSpeed * 1.25);
        ball.horizontalSpeed = (float)(ball.currentSpeed * .75);
        break;
    default:
        break;
    }
}

void ResetBall(Ball& ball, Direction direcion) {
    if (!ball.bonus) {
        HalveBallSpeed(ball); // Bajamos la velocidad de la pelota por la mitad.
        ball.pos.x = GetScreenWidth() * .5;
        switch (GetRandomValue(0, 2)) {
        case 0:
            ball.pos.y = GetScreenHeight() * .25;
            break;
        case 1:
            ball.pos.y = GetScreenHeight() * .5;
            break;
        case 2:
            ball.pos.y = GetScreenHeight() * .75;
            break;
        default:
            break;
        }
        ball.ax.x = (GetRandomValue(0, 1) ? Direction::UP : Direction::DOWN);
        ball.ax.y = direcion;
        if (IsThereFrenzy()) {
            Unfrenzy(ball);
        }
        RandomizeAngle(ball);
    }
    else {
        ball.pos.x = GetScreenWidth() * .5;
        ball.pos.y = GetScreenWidth() * .5;
        DespawnBonusBall(ball);
    }
    HaltGame(); // Hacemos que la pelota se quede quieta unos segundos.
}

void ResetBallRandom(Ball& ball) {
    if (!ball.bonus) { // Solo frenar el juego si es una pelota normal.
        HaltGame();
    }
    ball.pos.x = GetScreenWidth() * .5;
    ball.pos.y = GetScreenHeight() * .5;
    ball.ax.x = (GetRandomValue(0, 1) ? Direction::UP : Direction::DOWN);
    ball.ax.y = (GetRandomValue(0, 1) ? Direction::LEFT : Direction::RIGHT);
    SetAngle(ball, Angle::NORMAL);
}

void BallDirectionManager(Ball& ball, Player ply) {
    if (ball.ax.x == Direction::DOWN) {
        if (ball.pos.y < ply.pos.y) {
            ball.pos.y = ply.pos.y - ball.radius;
            ball.ax.x = Direction::UP;
        }
    }
    else {
        if (ball.pos.y > (ply.pos.y + ply.tall)) {
            ball.pos.y = ply.pos.y + ply.tall + ball.radius;
            ball.ax.x = Direction::DOWN;
        }
    }
}

void HalveBallSpeed(Ball& ball) {
    ball.currentSpeed = (((ball.currentSpeed - ball.baseSpeed) * .5) + ball.baseSpeed); // Cortamos la velocidad ganada por la mitad.
    std::cout << "Velocidad reducida!\n";
}

void IncreaseBallSpeed(Ball& ball) {
    if (GetGameTime() > ball.cooldown) {
        ball.currentSpeed = ball.currentSpeed * speedIncrease;
        ball.cooldown = GetGameTime() + speedInterval;
        std::cout << "Velocidad de la pelota: " << ball.currentSpeed << ".\n";
    }
}

void BallSpeedManager(Ball& ball, Player ply) {
    IncreaseBallSpeed(ball);
    if (ball.ax.x == Direction::UP) {
        switch (ply.dir)
        {
        case Direction::UP:
            SetAngle(ball, Angle::NARROW);
            break;
        case Direction::DOWN:
            SetAngle(ball, Angle::WIDE);
            break;
        default:
            SetAngle(ball, Angle::NORMAL);
            break;
        }
    }
    else {
        switch (ply.dir)
        {
        case Direction::UP:
            SetAngle(ball, Angle::WIDE);
            break;
        case Direction::DOWN:
            SetAngle(ball, Angle::NARROW);
            break;
        default:
            SetAngle(ball, Angle::NORMAL);
            break;
        }
    }
}

void BallBehaviourManager(Ball& ball, Player ply) {
    BallSpeedManager(ball, ply);
    BallDirectionManager(ball, ply);
}

void SwitchDirection(Ball ball, Direction& dir) {
    if (dir == Direction::UP || dir == Direction::DOWN) {
        (ball.pos.y < (GetScreenHeight() / 2)) ? dir = Direction::DOWN : dir = Direction::UP;
    }
    else {
        (ball.pos.x < (GetScreenWidth() / 2)) ? dir = Direction::RIGHT : dir = Direction::LEFT;
    }
}

void BallPlayerCollision(Player ply, Ball& ball) {
    if (ply.pos.x < ball.pos.x + ball.radius &&
        ply.pos.x + ply.wide > ball.pos.x - ball.radius &&
        ply.pos.y < ball.pos.y + ball.radius &&
        ply.tall + ply.pos.y > ball.pos.y - ball.radius) {
        BallBehaviourManager(ball, ply);
        SwitchDirection(ball, ball.ax.y);
    }
}

void BallWallCollision(Ball& ball) {
    if (ball.pos.y + ball.radius > GetScreenHeight()) {
        SwitchDirection(ball, ball.ax.x);
        ball.pos.y = GetScreenHeight() - ball.radius; // En caso de que la pelota se pase, la acomodo.
    }

    if (ball.pos.y - ball.radius < 0) {
        SwitchDirection(ball, ball.ax.x);
        ball.pos.y = 0 + ball.radius;
    }

    if (ball.pos.x + ball.radius > GetScreenWidth()) {
        AddPoints(Direction::LEFT); // Añadimos puntos al jugador del lado opuesto.
        ResetBall(ball, Direction::RIGHT);
    }
    if (ball.pos.x - ball.radius < 0) {
        AddPoints(Direction::RIGHT);
        ResetBall(ball, Direction::LEFT);
    }
}

void MoveBall(Ball& ball, Direction dir, float speed) {
    switch (dir)
    {
    case Direction::UP:
        ball.pos.y -= speed * GetFrameTime();
        break;
    case Direction::DOWN:
        ball.pos.y += speed * GetFrameTime();
        break;
    case Direction::LEFT:
        ball.pos.x -= speed * GetFrameTime();
        break;
    case Direction::RIGHT:
        ball.pos.x += speed * GetFrameTime();
        break;
    default:
        break;
    }
}

void UpdateBall(Ball& ball, Player player1, Player player2, Bumps& bumps) {
    MoveBall(ball, ball.ax.x, ball.verticalSpeed);
    MoveBall(ball, ball.ax.y, ball.horizontalSpeed);
    BallWallCollision(ball);

    if (ball.pos.x < (GetScreenWidth() / 2)) { // Depende de que lado de la pantalla se encuentre, checkear colision con el player adecuado.
        BallPlayerCollision(player1, ball);
    }
    else {
        BallPlayerCollision(player2, ball);
    }
    // Bumps
    if (ball.pos.y < (GetScreenHeight() * .5)) {
        if(IsSpeedbumpActive(bumps.top))
            BallSpeedbumpCollision(bumps.top, ball);
    }
    else {
        if (IsSpeedbumpActive(bumps.bottom))
            BallSpeedbumpCollision(bumps.bottom, ball);
    }
}

void DrawBall(Ball ball) {
	DrawCircle(ball.pos.x, ball.pos.y, ball.radius, ball.color);
}

Ball CreateBall(Color color) {
	Ball ball;
	ball.radius = GetScreenHeight() * .02;
	ball.color = color;
	ball.baseSpeed = GetScreenWidth() * .35; // La velocidad base de la pelota depende del ancho de la pantalla.
    ball.currentSpeed = ball.baseSpeed;
    ball.horizontalSpeed = ball.currentSpeed;
    ball.verticalSpeed = ball.currentSpeed;
    ball.ax.x = Direction::STILL;
    ball.ax.y = Direction::STILL;
    ball.pos.x = 0;
    ball.pos.y = 0;

	return ball;
}

void InitBonusBall(Ball& ball) {
    ball = CreateBall(ORANGE);
    ball.bonus = true;
    ball.pos = { (float)(GetScreenWidth() * .5), (float)(GetScreenHeight() * .5) };
    ball.cooldown = GetGameTime() + (speedInterval * 3);
    ResetBallRandom(ball);
}

void InitBall(Ball& ball) {
	ball = CreateBall(GREEN);
    ball.bonus = false;
	ball.pos = { (float)(GetScreenWidth() * .5), (float)(GetScreenHeight() * .5) };
    ball.cooldown = GetGameTime() + (speedInterval * 3); // Damos un breathing room antes de comenzar a aumentar la velocidad.
    ResetBallRandom(ball);
}