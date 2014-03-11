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
void gameSetBackgroundPicture(int* pixels, int width, int height);
void gameRequestScreenshot(const char* filePath);

GUI* gui();
Camera* camera();
Camera* rtCamera();

#endif // __FASHION_GAME_H__
