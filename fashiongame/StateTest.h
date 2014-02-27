#ifndef __STATETEST_H__
#define __STATETEST_H__

#include "utils/GameState.h"
#include "Camera.h"

class StateTest : public GameState
{
public:
	StateTest();
	static StateTest* instance();

	virtual void destroy();
	
	virtual void begin();
	virtual void end();
	virtual void update();
	virtual void render();	
	virtual void onGUI();
};

#endif // __STATETEST_H__
