#ifndef __MATERIAL_H__
#define __MATERIAL_H__

#include "Shader.h"
#include "Texture.h"

class Material : public SharedObject
{
	friend class RenderState;

public:
	static Material* create(int name, Shader* shader);
	virtual void destroy();

	inline int name() const { return m_name; }
	inline Shader* shader() const { return m_shader; }
	inline int sortingType() const { return m_sortingType; }

	void setTexture(int idx, Texture* tex);

	void begin();
	void endShader();
	void endTexturing();

private:
	Material(int name, Shader* shader);
	~Material();

	Shader* m_shader;
	int m_name;
	int m_sortingType;
	Texture* m_textures[MAX_TEXTURE_UNITS];
};

#endif // __MATERIAL_H__
