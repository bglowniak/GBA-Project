#include <stdio.h>
#include "myLib.h"
#include "graphics.h"
#include "game.h"

extern unsigned short *videoBuffer;
extern LEVEL level_1;

enum GBAState {
	START,
	START_NODRAW,
	INIT,
	GAME,
	GAME_OVER,
	GAME_OVER_NODRAW
};

typedef struct {
	PLAYER* player;
	LEVEL* currentLevel;
} GameState;

int main() {
	REG_DISPCTL = MODE3 | BG2_ENABLE;

	enum GBAState state = START;
	LEVEL currentLevel;
	PLAYER player;
	GameState gameState = {
		&player,
		&currentLevel
	};
	int startPressed = FALSE;

	while(1) {
		waitForVblank();
		switch(state) {
			case START:
				drawSplashScreen();
				state = START_NODRAW;
				break;
			case START_NODRAW:
				if (!startPressed && KEY_DOWN_NOW(BUTTON_START)) {
					state = GAME;
					startPressed = TRUE;
				}
				break;
			case INIT:
				clearScreen();
				LEVEL currentLevel = level_1;
				PLAYER player = {currentLevel.playerStartX, currentLevel.playerStartY, 0};
				(void) player;
				(void) gameState;
				state = GAME;
				break;
			case GAME:
				if (KEY_DOWN_NOW(BUTTON_SELECT)) {
					state = START;
				}
				break;
			case GAME_OVER:
				drawGameOver();
				state = GAME_OVER_NODRAW;
				break;
			case GAME_OVER_NODRAW:
				if (!startPressed && KEY_DOWN_NOW(BUTTON_START)) {
					state = START;
					startPressed = TRUE;
				}
				break;
		}

		if (!KEY_DOWN_NOW(BUTTON_START)) {
			startPressed = FALSE;
		}
	}
}
