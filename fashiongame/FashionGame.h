#ifndef __FASHION_GAME_H__
#define __FASHION_GAME_H__

#include "gui/GUI.h"

void gameSetup();
void gameInit();
void gameDestroy();

void gameUpdate();
void gameRender();

GUI* gui();

#endif // __FASHION_GAME_H__
