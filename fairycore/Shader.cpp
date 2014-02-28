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
, m_strVertexShader(NULL)
, m_strFragmentShader(NULL)
, m_shaderProgram(0)
, m_vertexShader(0)
, m_fragmentShader(0)
{	
	m_uniforms = new(true) Array<SPVRTPFXUniform>();

	setDefaults();
	load(StreamReader::create(MemoryStream::create(data, length)));	
}

Shader::~Shader()
{
	cleanShaderProgram(m_shaderProgram, m_vertexShader, m_fragmentShader);

	SAFE_RELEASE(m_name);
	SAFE_RELEASE(m_strVertexShader);
	SAFE_RELEASE(m_strFragmentShader);

	for (int i = 0; i < m_uniforms->count(); ++i)
	{
		ByteArray* str = m_uniforms->get(i).sValueName;
		SAFE_RELEASE(str);
	}
	POOL(Array<SPVRTPFXUniform>)->deallocate(m_uniforms);
}

void Shader::load(StreamReader* reader)
{
	reader->retain();
	while (!reader->endOfStream())
	{
		ByteArray* line = reader->readLineToBytes();

		if (line)
		{
			line->trim();

			if (line->equals("[EFFECT]"))
			{
				processEffectInfo(reader);
			}
			else if (line->equals("[VERTEXSHADER]"))
			{
				m_strVertexShader = ByteArray::create(false);
				processShader(reader, "[/VERTEXSHADER]", m_strVertexShader);
			}
			else if (line->equals("[FRAGMENTSHADER]"))
			{
				m_strFragmentShader = ByteArray::create(false);
				processShader(reader, "[/FRAGMENTSHADER]", m_strFragmentShader);
			}
		}

		SharedObject::autoReleaseGC();
	}

	build();
	reader->release();
}

void Shader::build()
{
	m_vertexShader = compileVertexShader(m_strVertexShader->cstr());
	m_fragmentShader = compileFragmentShader(m_strFragmentShader->cstr());
	m_shaderProgram = linkShaderProgram(m_vertexShader, m_fragmentShader);

	const SPVRTPFXUniformSemantic* semantics = PVRTPFXSemanticsGetSemanticList();

	for (int i = 0; i < m_uniforms->count(); ++i)
	{
		SPVRTPFXUniform& uniform = m_uniforms->get(i);
		const SPVRTPFXUniformSemantic& semantic = semantics[uniform.nSemantic];

		if (semantic.isAttrib)
		{
			uniform.nLocation = glGetAttribLocation(m_shaderProgram, uniform.sValueName->cstr());
			m_isAttributeRequired[semantic.n] = true;			
			++m_numAttributesRequired;
		}
		else
		{
			uniform.nLocation = glGetUniformLocation(m_shaderProgram, uniform.sValueName->cstr());

			// Check for array. Workaround for some OpenGL:ES implementations which require array element appended to uniform name
			// in order to return the correct location.
			if (uniform.nLocation == -1)
			{
				ByteArray* szTmpUniformName = ByteArray::create(uniform.sValueName->cstr());
				szTmpUniformName->append("[0]");
				uniform.nLocation = glGetUniformLocation(m_shaderProgram, szTmpUniformName->cstr());
			}
		}
	}
}

void Shader::setDefaults()
{
	m_name = ByteArray::create();
	m_renderQueue = RENDER_QUEUE_GEOMETRY;
	m_isZWriting = true;

	m_faceCullingMode = GL_FRONT_AND_BACK;

	m_isAlphaBlending = false;
	m_blendingSource = GL_SRC_ALPHA;
	m_blendingDest = GL_ONE_MINUS_SRC_ALPHA;

	m_depthFunc = GL_ALWAYS;

	for (int i = 0; i < SEMANTIC_ATTRIBUTES_NUM; ++i)
	{
		m_isAttributeRequired[i] = false;
	}
	m_numAttributesRequired = 0;
}

void Shader::processEffectInfo(StreamReader* reader)
{
	while (!reader->endOfStream())
	{
		SharedObject::autoReleaseGC();

		ByteArray* line = reader->readLineToBytes();

		if (line)
		{
			line->trim();

			if (line->equals("[/EFFECT]"))
			{
				return;
			}
			else
			{
				List* params = line->split(NULL, 0);

				if (params->count() >= 2)
				{
					ByteArray* param0 = (ByteArray*)params->get(0);
					ByteArray* param1 = (ByteArray*)params->get(1);
					param0->toUpper();					

					// Name
					if (param0->equals("NAME"))
					{
						m_name = param1;
						m_name->retain();
					}
					// Depth sorting
					else if (param0->equals("RENDERQUEUE"))
					{
						m_renderQueue = parseRenderQueueFromString(param1);
					}
					// Z-Writing
					else if (param0->equals("ZWRITE"))
					{
						m_isZWriting = param1->equalsIgnoreCase("On");
					}
					// Face Culling
					else if (param0->equals("FACECULL"))
					{
						m_faceCullingMode = cullModeFromString(param1);						
					}
					else if (param0->equals("ZTEST"))
					{
						if (param1->equalsIgnoreCase("Off"))
						{
							m_depthFunc = GL_ALWAYS;
						}
						else
						{
							m_depthFunc = depthFuncFromString(param1);
						}
					}
					else if (params->count() >= 3)
					{
						ByteArray* param2 = (ByteArray*)params->get(2);

						if (param0->equals("BLENDING"))
						{
							m_isAlphaBlending = true;							
							m_blendingSource = alphaFactorFromString(param1);
							m_blendingDest = alphaFactorFromString(param2);
						}
						else if (param0->equals("ATTRIBUTE") || param0->equals("UNIFORM"))
						{
							SPVRTPFXUniform uniform;

							// Variable name
							uniform.sValueName = param1;
							param1->retain();

							// Semantic index
							ByteArray* temp = ByteArray::create(param2->cstr());
							if (ByteArray::isNumeric(temp->cstr()[param2->length() - 1]))
							{
								temp->subString(0, param2->length() - 1);
							}

							int len = 0;
							const SPVRTPFXUniformSemantic* semantics = PVRTPFXSemanticsGetSemanticList();
							uniform.nSemantic = 0;
							for (int i = 0; i < ePVRTPFX_NumSemantics; ++i)
							{
								if (temp->equalsIgnoreCase(semantics[i].p))
								{
									len = (int)strlen(semantics[i].p);
									uniform.nSemantic = i;
									break;
								}								
							}		
	
							uniform.nIdx = len < param2->length() ? param2->cstr()[len] - '0' : 0;

							// Location to be retrieve when compiling shader
							uniform.nLocation = 0;

							m_uniforms->add(uniform);
						}
					}
				}
			}
		}
	}
}

GLenum Shader::alphaFactorFromString(ByteArray* str)
{
	if (str->equalsIgnoreCase("SrcAlpha"))
	{
		return GL_SRC_ALPHA;
	}
	else if (str->equalsIgnoreCase("OneMinusSrcAlpha"))
	{
		return GL_ONE_MINUS_SRC_ALPHA;
	}	
	else if (str->equalsIgnoreCase("One"))
	{
		return GL_ONE;
	}
	else if (str->equalsIgnoreCase("SrcColor"))
	{
		return GL_SRC_COLOR;
	}
	else if (str->equalsIgnoreCase("OneMinusSrcColor"))
	{
		return GL_ONE_MINUS_SRC_COLOR;
	}
	else if (str->equalsIgnoreCase("DstAlpha"))
	{
		return GL_DST_ALPHA;
	}
	else if (str->equalsIgnoreCase("OneMinusDstAlpha"))
	{
		return GL_ONE_MINUS_DST_ALPHA;
	}

	return GL_ZERO;
}

GLenum Shader::cullModeFromString(ByteArray* str)
{
	if (str->equalsIgnoreCase("Front"))
	{
		return GL_FRONT;
	}
	else if (str->equalsIgnoreCase("Back"))
	{
		return GL_BACK;
	}
	
	return GL_FRONT_AND_BACK;
}

GLenum Shader::renderTypeFromString(ByteArray* str)
{
	return 0;

	/*if (str->equalsIgnoreCase("Transparent"))
	{
		return GL_RENDER_TYPE_TRANSPARENT;
	}
	
	return GL_RENDER_TYPE_OPAQUE;*/	
}

int Shader::parseRenderQueueFromString(ByteArray* str)
{
	int baseQueue = 0;
	if (str->startsWithIgnoreCase("Geometry"))
	{
		baseQueue = RENDER_QUEUE_GEOMETRY;
	}
	else if (str->startsWithIgnoreCase("Transparent"))
	{
		baseQueue = RENDER_QUEUE_TRANSPARENT;
	}
	if (str->startsWithIgnoreCase("Overlay"))
	{
		baseQueue = RENDER_QUEUE_OVERLAY;
	}

	int idx;
	
	idx = str->indexOf('+');
	if (idx < 0)
	{
		idx = str->indexOf('-');

		// Minus
		if (idx >= 0)
		{
			ByteArray* temp = ByteArray::create(str->cstr());
			temp->subString(idx + 1);
			return baseQueue - temp->toInt();
		}		
	}
	// Plus
	else
	{
		ByteArray* temp = ByteArray::create(str->cstr());
		temp->subString(idx + 1);
		return baseQueue + temp->toInt();
	}

	// Nothing
	return baseQueue;
}

GLenum Shader::depthFuncFromString(ByteArray* str)
{
	if (str->equalsIgnoreCase("Never"))
	{
		return GL_NEVER;
	}
	else if (str->equalsIgnoreCase("Less"))
	{
		return GL_LESS;
	}
	else if (str->equalsIgnoreCase("Equal"))
	{
		return GL_EQUAL;
	}
	else if (str->equalsIgnoreCase("LEqual"))
	{
		return GL_LEQUAL;
	}
	else if (str->equalsIgnoreCase("Greater"))
	{
		return GL_GREATER;
	}
	else if (str->equalsIgnoreCase("NotEqual"))
	{
		return GL_NOTEQUAL;
	}
	else if (str->equalsIgnoreCase("GEqual"))
	{
		return GL_GEQUAL;
	}

	return GL_ALWAYS;
}

void Shader::processShader(StreamReader* reader, const char* endtag, ByteArray* soureCode)
{
	while (!reader->endOfStream())
	{
		ByteArray* line = reader->readLineToBytes();

		if (line)
		{
			line->trim();

			if (line->equals(endtag))
			{
				return;
			}
			else if (line->equals("[GLSL]"))
			{
				while (!reader->endOfStream())
				{
					ByteArray* line = reader->readLineToBytes();

					if (line)
					{
						line->trim();

						if (line->equals("[/GLSL]"))
						{
							break;
						}
						else
						{
							soureCode->append(line->cstr());
						}
					}
				}				
			}
		}

		SharedObject::autoReleaseGC();
	}
}

GLuint Shader::compileVertexShader(const char* source)
{
	GLint bShaderCompiled;
	GLuint uiVertShader = glCreateShader(GL_VERTEX_SHADER);

	glShaderSource(uiVertShader, 1, &source, NULL);
	glCompileShader(uiVertShader);
	glGetShaderiv(uiVertShader, GL_COMPILE_STATUS, &bShaderCompiled);
	if (!bShaderCompiled)
	{
		/*
#ifndef NO_GDI
		int i32InfoLogLength, i32CharsWritten;
		glGetShaderiv(uiVertShader, GL_INFO_LOG_LENGTH, &i32InfoLogLength);
		char* pszInfoLog = new char[i32InfoLogLength];
		glGetShaderInfoLog(uiVertShader, i32InfoLogLength, &i32CharsWritten, pszInfoLog);

		MessageBox(NULL, i32InfoLogLength ? pszInfoLog : "", "Failed to compile vertex shader", MB_OK | MB_ICONEXCLAMATION);

		delete[] pszInfoLog;
#endif
		*/
		return 0;
	}

	return uiVertShader;
}

GLuint Shader::compileFragmentShader(const char* source)
{
	// Create the fragment shader object
	GLuint uiFragShader = glCreateShader(GL_FRAGMENT_SHADER);

	// Load the source code into it
	glShaderSource(uiFragShader, 1, &source, NULL);

	// Compile the source code
	glCompileShader(uiFragShader);

	// Check if compilation succeeded
	GLint bShaderCompiled;
	glGetShaderiv(uiFragShader, GL_COMPILE_STATUS, &bShaderCompiled);

	if (!bShaderCompiled)
	{
/*#ifndef NO_GDI
		// An error happened, first retrieve the length of the log message
		int i32InfoLogLength, i32CharsWritten;
		glGetShaderiv(uiFragShader, GL_INFO_LOG_LENGTH, &i32InfoLogLength);

		// Allocate enough space for the message and retrieve it
		char* pszInfoLog = new char[i32InfoLogLength];
		glGetShaderInfoLog(uiFragShader, i32InfoLogLength, &i32CharsWritten, pszInfoLog);

		// Displays the error in a dialog box
		MessageBox(NULL, i32InfoLogLength ? pszInfoLog : _T(""), _T("Failed to compile fragment shader"), MB_OK | MB_ICONEXCLAMATION);

		delete[] pszInfoLog;
#endif*/
		return 0;
	}

	return uiFragShader;
}

GLuint Shader::linkShaderProgram(GLuint vshader, GLuint fshader)
{
	// Create the shader program
	GLuint uiProgramObject = glCreateProgram();

	// Attach the fragment and vertex shaders to it
	glAttachShader(uiProgramObject, fshader);
	glAttachShader(uiProgramObject, vshader);

	// Link the program
	glLinkProgram(uiProgramObject);

	// Check if linking succeeded in the same way we checked for compilation success
	GLint bLinked;
	glGetProgramiv(uiProgramObject, GL_LINK_STATUS, &bLinked);
	if (!bLinked)
	{
/*#ifndef NO_GDI
		int i32InfoLogLength, i32CharsWritten;
		glGetProgramiv(uiProgramObject, GL_INFO_LOG_LENGTH, &i32InfoLogLength);
		char* pszInfoLog = new char[i32InfoLogLength];
		glGetProgramInfoLog(uiProgramObject, i32InfoLogLength, &i32CharsWritten, pszInfoLog);

		MessageBox(NULL, i32InfoLogLength ? pszInfoLog : _T(""), _T("Failed to link program"), MB_OK | MB_ICONEXCLAMATION);

		delete[] pszInfoLog;
#endif*/
		return 0;
	}

	return uiProgramObject;
}

void Shader::cleanShaderProgram(GLuint uiProgramObject, GLuint uiFragShader, GLuint uiVertShader)
{
	if (uiProgramObject)
	{
		glDeleteProgram(uiProgramObject);
	}
	if (uiFragShader)
	{
		glDeleteShader(uiFragShader);
	}
	if (uiVertShader)
	{
		glDeleteShader(uiVertShader);
	}
}

bool Shader::isAttributeRequired(int n) const
{
	return m_isAttributeRequired[n];
}

int Shader::numAttributesRequired() const
{
	return m_numAttributesRequired;
}

Array<SPVRTPFXUniform>& Shader::uniforms() const
{
	return *m_uniforms;
}

GLuint Shader::shaderProgram() const
{
	return m_shaderProgram;
}

int Shader::getRenderQueue() const
{
	return m_renderQueue;
}
