#ifndef __MATERIAL_H__
#define __MATERIAL_H__

#include "Shader.h"

class Material : public SharedObject
{
public:
	static Material* create(Shader* shader);
	virtual void destroy();

	int guid() const;	
	Shader* shader() const;

private:
	Material(Shader* shader);
	~Material();

	Shader* m_shader;
	int m_guid;
};

#endif // __MATERIAL_H__
