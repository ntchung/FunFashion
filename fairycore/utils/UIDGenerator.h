#ifndef __UIDGENERATOR_H__
#define __UIDGENERATOR_H__

#include "utils/SharedObject.h"

class UIDGenerator : public SharedObject
{
public:
	static UIDGenerator* shared();
	virtual void destroy();

	int next();

private:
	UIDGenerator();
	~UIDGenerator();

	int m_loop;
};

#endif // __UIDGENERATOR_H__
