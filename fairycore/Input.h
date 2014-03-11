#ifndef __INPUT_H__
#define __INPUT_H__

#include "utils/SharedObject.h"
#include "maths/Vector2f.h"

enum TouchPhase
{
	Began = 0,
	Moved,
	Stationary,
	Ended,
	Canceled
};

struct Touch
{
public:
	Vector2f deltaPosition;
	unsigned int deltaTime;
	int fingerId;
	TouchPhase phase;
	Vector2f position;
	Vector2f rawPosition;
	int tapCount;
	unsigned int lastTime;

	Touch(int fid, TouchPhase ph, int x, int y);
};

class Input : public SharedObject
{
public:
	static Input* shared();
	virtual void destroy();

	inline const Touch& getTouch(int index) const { return m_touches->get(index); }
	inline int touchCount() const { return m_touches->count(); }

	void onTouchEvent(TouchPhase phase, int fingerId, int x, int y);

private:
	Input();
	~Input();

	Array<Touch>* m_touches;
};

#endif // __INPUT_H__
