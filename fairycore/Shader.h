#ifndef __SHADER_H__
#define __SHADER_H__

#include "utils/SharedObject.h"

class Shader : public SharedObject
{
public:
	static Shader* create(const char* data);
	virtual void destroy();

private:
	Shader(const char* data);
	~Shader();
};

#endif // __SHADER_H__
