#ifndef __FASHION_GAME_H__
#define __FASHION_GAME_H__

#include "gui/GUI.h"

void gameSetup();
void gameInit();
void gameDestroy();

void gameUpdate();
void gameRender();

void gameSetScreenSize(int width, int height);

GUI* gui();

#endif // __FASHION_GAME_H__
