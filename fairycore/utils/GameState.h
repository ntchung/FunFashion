#ifndef __GAMESTATE_H__
#define __GAMESTATE_H__

#include "utils/SharedObject.h"

class GameState : public SharedObject
{
public:	
	GameState()
	{
		autorelease();
		retain();
	}

	virtual void begin() = 0;
	virtual void end() = 0;
	virtual void update() = 0;
	virtual void render() = 0;
};

#endif // __GAMESTATE_H__
