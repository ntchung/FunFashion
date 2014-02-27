#ifndef __SHADER_H__
#define __SHADER_H__

#include <GLES2/gl2.h>
#include "utils/SharedObject.h"
#include "utils/StreamReader.h"
#include "utils/ByteArray.h"
#include "utils/Array.h"
#include "utils/PVRTPFXSemantics.h"

struct SPVRTPFXUniform
{
	unsigned int	nLocation;		// GL location of the Uniform 
	unsigned int	nSemantic;		// Application-defined semantic value 
	unsigned int	nIdx;			// Index; for example two semantics might be LIGHTPOSITION0 and LIGHTPOSITION1 
	ByteArray*		sValueName;		// The name of the variable referenced in shader code 
};

class Shader : public SharedObject
{
	friend class RenderState;

public:
	static Shader* create(char* data, int length);
	virtual void destroy();

	bool isAttributeRequired(int n) const;
	int numAttributesRequired() const;

	GLuint shaderProgram() const;

	Array<SPVRTPFXUniform>& uniforms() const;

	GLenum getRenderType() const;
	int getRenderQueue() const;

	void begin();
	void end();

private:
	Shader(char* data, int length);
	~Shader();

	void load(StreamReader* reader);
	void processEffectInfo(StreamReader* reader);
	void processShader(StreamReader* reader, const char* endtag, ByteArray* soureCode);
	void build();

	ByteArray* m_name;
	Array<SPVRTPFXUniform>* m_uniforms;
	ByteArray* m_strVertexShader;
	ByteArray* m_strFragmentShader;

	int m_renderQueue;	
	bool m_isZWriting;

	GLenum m_renderType;

	GLenum m_faceCullingMode;

	bool m_isAlphaBlending;
	GLenum m_blendingSource;
	GLenum m_blendingDest;

	GLenum m_depthFunc;

	GLuint m_shaderProgram;
	GLuint m_vertexShader;
	GLuint m_fragmentShader;

	bool m_isAttributeRequired[SEMANTIC_ATTRIBUTES_NUM];
	int m_numAttributesRequired;

	void setDefaults();

	static GLenum alphaFactorFromString(ByteArray* str);
	static GLenum cullModeFromString(ByteArray* str);
	static GLenum renderTypeFromString(ByteArray* str);
	static GLenum depthFuncFromString(ByteArray* str);

	static GLuint compileVertexShader(const char* source);
	static GLuint compileFragmentShader(const char* source);
	static GLuint linkShaderProgram(GLuint vshader, GLuint fshader);
	static void cleanShaderProgram(GLuint uiProgramObject, GLuint uiFragShader, GLuint uiVertShader);
};

#endif // __SHADER_H__
