#include "stdafx.h"

Shader* Shader::create(char* data, int length)
{
	return new(true) Shader(data, length);
}

void Shader::destroy()
{
	this->~Shader();
	POOL(Shader)->deallocate(this);
}

Shader::Shader(char* data, int length)
: m_name(NULL)
{
	StreamReader* reader = StreamReader::create(MemoryStream::create(data, length));
	
	int i = 0;
	while (!reader->endOfStream())
	{
		String* line = reader->readLine();

		if (line)
		{
			line->trim();

			if (line->equals("[EFFECT]"))
			{
				processEffectInfo(reader);
			}
		}				
	}
}

Shader::~Shader()
{
	SAFE_RELEASE(m_name);
}

void Shader::processEffectInfo(StreamReader* reader)
{
	return;

	while (!reader->endOfStream())
	{
		String* line = reader->readLine();

		if (line)
		{
			line->trim();
			if (line->equals("[/EFFECT]"))
			{
				return;
			}
			else
			{

			}
		}
	}
}
