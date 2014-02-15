#ifndef __SHADER_H__
#define __SHADER_H__

#include "utils/SharedObject.h"
#include "utils/StreamReader.h"

class Shader : public SharedObject
{
public:
	static Shader* create(char* data, int length);
	virtual void destroy();

private:
	Shader(char* data, int length);
	~Shader();

	void processEffectInfo(StreamReader* reader);

	String* m_name;
};

#endif // __SHADER_H__
