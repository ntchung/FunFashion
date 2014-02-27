#ifndef __MATERIAL_H__
#define __MATERIAL_H__

#include "Shader.h"

class Material : public SharedObject
{
public:
	static Material* create(int name, Shader* shader);
	virtual void destroy();

	inline int name() const { return m_name; }
	Shader* shader() const;

private:
	Material(int name, Shader* shader);
	~Material();

	Shader* m_shader;
	int m_name;
};

#endif // __MATERIAL_H__
