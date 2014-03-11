#ifndef __TIME_H__
#define __TIME_H__

#include "utils/SharedObject.h"

class Timer : public SharedObject
{ 
public:
	static Timer* shared();
	virtual void destroy();

	inline int time() const { return m_time; }
	inline int deltaTime() const { return m_deltaTime;  }
	inline int frameCount() const { return m_frameCount; }

	inline int timeScale() const { return m_timeScale; }
	inline void setTimeScale(int value) { m_timeScale = value; }

	void update(unsigned int dt);

	static long long getRealTime();

private:
	Timer();
	~Timer();

	unsigned int m_time;
	unsigned int m_deltaTime;
	unsigned int m_frameCount;
	unsigned int m_timeScale;	
};

#endif // __TIME_H__
