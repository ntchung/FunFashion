#include "stdafx.h"
#include <time.h>

static Timer* g_sharedTime = 0;

Timer* Timer::shared()
{
	if (!g_sharedTime)
	{
		g_sharedTime = new Timer();
		g_sharedTime->autorelease();
		g_sharedTime->retain();
	}

	return g_sharedTime;
}
	
void Timer::destroy()
{
	this->~Timer();
	delete this;
}

Timer::Timer()
: m_time(0)
, m_deltaTime(0)
, m_frameCount(0)
, m_timeScale(256)
{
}

Timer::~Timer()
{
}

void Timer::update(unsigned int dt)
{
	m_deltaTime = ( dt * m_timeScale ) >> 8;
	m_time += m_deltaTime;
	++m_frameCount;
}
