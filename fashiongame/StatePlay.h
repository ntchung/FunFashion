#ifndef __STATEPLAY_H__
#define __STATEPLAY_H__

#include "utils/GameState.h"

class PictureRenderer;
class Texture;

class StatePlay : public GameState
{
public:
	StatePlay();
	static StatePlay* instance();

	virtual void destroy();
	
	virtual void begin();
	virtual void end();
	virtual void update();
	virtual void render();	
	virtual void onGUI();

	void setRotateRight(bool value);

private:
	~StatePlay();

	PictureRenderer* m_pictureRenderer;	
	PictureRenderer* m_rtRenderer;	
	PictureRenderer* m_shirtRenderer;
	Texture* m_backgroundPicture;
	bool m_isInitialized;
};

#endif // __STATEPLAY_H__
