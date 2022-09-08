#include "SettingsMenu.h"
#include "game/GameManager.h" // Para cambiar el estado a main menu.
#include <iostream>

namespace Settings {

	const int amountButtons = (int)SettingsOptions::COUNT;
	Button menuButtons[amountButtons];
	int menuCursor;

	int currentResolution;
	bool fullscreen;

	void CenterWindow(); // Centra la ventana en el medio de la pantalla.
	void SetResolution(Resolution res);
	void MyToggleFullscreen(); // Por que raylib tiene una funcion que se llama igual.
	void ChangeResolution(Resolutions id);
	Resolution GetResolutionValue(Resolutions id); // Le tiras el numero de una resolucion del enum y te devuelve los valores.
	const char* GetResolutionName(Resolutions id); // Igual que la anterior pero te devuelve un string con el nombre.
	void ChooseOption(SettingsOptions id);
	void DrawMenuButtons();
	void InitMenuButtons();
	void DrawMenuText();
	void DrawMenu();
	void MenuInput();

	void CenterWindow() {
		int monitor = GetCurrentMonitor();
		Resolution monitorRes;
		monitorRes.width = GetMonitorWidth(monitor);
		monitorRes.height = GetMonitorHeight(monitor);
		Resolution windowRes = GetResolutionValue((Resolutions)currentResolution);
		SetWindowPosition((monitorRes.width * .5) - (windowRes.width * .5), (monitorRes.height * .5) - (windowRes.height * .5));
	}

	void SetResolution(Resolution res) {
		SetWindowSize(res.width, res.height);
		std::cout << "Resolution set to: " << res.width << "x" << res.height << "!\n";
	}

	void MyToggleFullscreen() {
		fullscreen = !fullscreen;
		if (fullscreen) { // Cambiar el nombre del boton y la resolucion.
			int monitor = GetCurrentMonitor();
			Resolution res;
			res.width = GetMonitorWidth(monitor);
			res.height = GetMonitorHeight(monitor);
			SetResolution(res);
			HideCursor(); // No mostramos el cursor si estamos en pantalla completa.
			menuButtons[(int)SettingsOptions::FULLSCREEN].text = "Windowed";
		}
		ToggleFullscreen();
		if (!fullscreen) { // Si se pasa a fullscreen, primero cambiar la resolucion y despues a pantalla completa. Sino hacer al revez. (Para que windows no haga quilombo)
			SetResolution(GetResolutionValue((Resolutions)currentResolution)); // Restaurar la resolucion a la actual si se sale de pantalla completa.
			CenterWindow();
			ShowCursor(); // Volvemos a mostrar el cursor al volver a modo ventana.
			menuButtons[(int)SettingsOptions::FULLSCREEN].text = "Fullscreen";
		}
		InitMenu(); // Inicializamos el menu para que las dimensiones de los botones se ajusten a la nueva resolucion.
	}

	void ChangeResolution(Resolutions id) {
		SetResolution(GetResolutionValue((Resolutions)currentResolution));
		CenterWindow();
		menuButtons[(int)SettingsOptions::CHANGERESOLUTION].text = GetResolutionName(id);
		InitMenu();
	}

	Resolution GetResolutionValue(Resolutions id) {
		Resolution res;
		switch (id)
		{
		case Resolutions::NORMAL:
			res = { 640, 480 };
			break;
		case Resolutions::BIGGER:
			res = { 1280, 720 };
			break;
		case Resolutions::WIDE:
			res = { 1280, 540 };
			break;
		case Resolutions::TALL:
			res = { 1280, 962 };
			break;
		default:
			res = { 640, 480 };
			std::cout << "Invalid id! [SettingsMenu.cpp - GetResolutionValue()]\n";
			break;
		}
		return res;
	}

	const char* GetResolutionName(Resolutions id) {
		const char* name;
		switch (id)
		{
		case Resolutions::NORMAL:
			name = "640x480";
			break;
		case Resolutions::BIGGER:
			name = "1280x720";
			break;
		case Resolutions::WIDE:
			name = "1280x540";
			break;
		case Resolutions::TALL:
			name = "1280x962";
			break;
		default:
			name = "Error";
			std::cout << "Invalid id! [SettingsMenu.cpp - GetCurrentResolutionName()]\n";
			break;
		}
		return name;
	}

	void ChooseOption(SettingsOptions id) {
		switch (id)
		{
		case SettingsOptions::CHANGERESOLUTION:
			if (!fullscreen) { // Solo permitir cambiar resolucion si el juego se encuentra en modo ventana.
				currentResolution++;
				if (currentResolution > (int)Resolutions::TALL) { // Rotar si pasa el maximo.
					currentResolution = 0;
				}
				ChangeResolution((Resolutions)currentResolution);
			}
			break;
		case SettingsOptions::FULLSCREEN:
			MyToggleFullscreen();
			break;
		case SettingsOptions::RETURNTOMENU:
			SetGameStatus(GameStatus::MAINMENU);
			break;
		default:
			std::cout << "Invalid id! [SettingsMenu.cpp - ChooseSettingsMenuOption()]\n";
			break;
		}
	}

	void DrawMenuButtons() {
		for (int i = 0; i < amountButtons; i++) {
			if (i == (int)SettingsOptions::CHANGERESOLUTION && fullscreen) {
				menuButtons[i].color = DARKGRAY;
			}
			else {
				menuButtons[i].color = RAYWHITE;
			}
			menuButtons[i].highlighted = (menuCursor == i);
			DrawButton(menuButtons[i]);
		}
	}

	void InitMenuButtons() {
		Button button;
		button.pos.x = GetScreenWidth() * .275;
		button.width = GetScreenWidth() * .45;
		button.height = GetScreenHeight() * .1;
		button.fontSize = button.height * .5;
		button.color = RAYWHITE;
		button.highlighted = false;

		for (int i = 0; i < amountButtons; i++) {
			button.pos.y = (GetScreenHeight() * .3) + (button.height * (i + 1)) + ((button.height * .35) * (i + 1));

			switch ((SettingsOptions)i)
			{
			case SettingsOptions::CHANGERESOLUTION:
				button.text = GetResolutionName((Resolutions)currentResolution);
				break;
			case SettingsOptions::FULLSCREEN:
				button.text = "Fullscreen";
				break;
			case SettingsOptions::RETURNTOMENU:
				button.text = "Return to Main Menu";
				break;
			default:
				button.text = "Error";
				std::cout << "Invalid id! [SettingsMenu.cpp - InitSettingsMenuButtons()]\n";
				break;
			}

			menuButtons[i] = button;
		}
	}

	void DrawMenuText() {
		Vector2 pos = { GetScreenWidth() * .5, GetScreenHeight() * .2 };
		DrawCenteredText("Settings", pos, GetScreenHeight() * .07, WHITE);
		pos = { (float)(GetScreenWidth() * .5), (float)(GetScreenHeight() * .38) };
		DrawCenteredText("Press enter to change the resolution of the window", pos, GetScreenHeight() * .04, WHITE);
	}

	void DrawMenu() {
		BeginDrawing();
		ClearBackground(BLACK);

		DrawMenuText();
		DrawMenuButtons();

		EndDrawing();
	}

	void MenuInput() {
		UpdateMenuInput(menuCursor, (int)SettingsOptions::CHANGERESOLUTION, (int)SettingsOptions::RETURNTOMENU);

		if (IsKeyPressed(KEY_ENTER)) {
			ChooseOption((SettingsOptions)menuCursor);
		}
		else if (IsKeyPressed(KEY_ESCAPE)) {
			SetGameStatus(GameStatus::MAINMENU);
		}
	}

	void MenuLoop() {
		MenuInput();
		DrawMenu();
	}

	void ResetSettings() {
		currentResolution = 0;
		fullscreen = false;
	}

	void InitMenu() {
		InitMenuButtons();
		menuCursor = 0;
	}
}