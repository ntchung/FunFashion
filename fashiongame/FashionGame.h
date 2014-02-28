#ifndef __FASHION_GAME_H__
#define __FASHION_GAME_H__

class GUI;
class Camera;

void gameSetup();
void gameInit();
void gameDestroy();

void gameUpdate();
void gameRender();

void gameSetScreenSize(int width, int height);

GUI* gui();
Camera* camera();

#endif // __FASHION_GAME_H__
