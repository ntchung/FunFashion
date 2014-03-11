#include "stdafx.h"

static Input* g_sharedInput = 0;

Input* Input::shared()
{
	if (!g_sharedInput)
	{
		g_sharedInput = new Input();
		g_sharedInput->autorelease();
		g_sharedInput->retain();
	}

	return g_sharedInput;
}

void Input::destroy()
{
	this->~Input();
	delete this;
}

Input::Input()
{
	m_touches = new(true) Array<Touch>();
}

Input::~Input()
{
	POOL(Array<Touch>)->deallocate(m_touches);
}

void Input::onTouchEvent(TouchPhase phase, int fingerId, int x, int y)
{
	for (int i = m_touches->count() - 1; i >= 0; --i)
	{
		Touch& touch = m_touches->get(i);
		if (touch.fingerId == fingerId)
		{
			Vector2f v((float)x, (float)y);

			if (touch.phase != Ended && touch.phase != Canceled)
			{
				touch.deltaPosition = v - touch.position;
				touch.deltaTime = Timer::shared()->time() - touch.lastTime;
				touch.lastTime = Timer::shared()->time();
			}
			else
			{
				touch.deltaPosition = Vector2f::zero;
				touch.deltaTime = 0;
				touch.lastTime = Timer::shared()->time();
			}

			touch.phase = phase;
			touch.position = v;
			touch.rawPosition = v;
			touch.tapCount = 0;			
			return;
		}
	}

	m_touches->add(Touch(fingerId, phase, x, y));
}

Touch::Touch(int fid, TouchPhase ph, int x, int y)
: deltaPosition(0, 0)
, deltaTime(0)
, fingerId(fid)
, phase(ph)
, position((float)x, (float)y)
, rawPosition((float)x, (float)y)
, tapCount(0)
, lastTime(Timer::shared()->time())
{
}
