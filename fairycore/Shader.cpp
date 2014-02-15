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

			/*if (line->equals("[EFFECT]"))
			{
				processEffectInfo(reader);
			}*/

			//line->release();
		}		

		++i;
		if (i == 7)
		{
			i = i;
		}
		if (i > 7)
		{
			char* temp = new char[line->length() + 1];
			for (int j = 0; j < line->length(); ++j)
			{
				temp[j] = line->getData()[j];
			}
			break;
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

		line->release();
	}
}
