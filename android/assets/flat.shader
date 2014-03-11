 [EFFECT] 
	NAME    Flat

	ATTRIBUTE inVertex				POSITION
	ATTRIBUTE inUV					UV0

	UNIFORM MVPMatrix			WORLDVIEWPROJECTION
	UNIFORM sTexture				TEXTURE0
	
	RENDERQUEUE					Overlay
	ZTEST									Off
	ZWRITE								Off
	FACECULL							Off
[/EFFECT]

[VERTEXSHADER]
	[GLSL]
	attribute mediump vec4 inVertex;
	attribute lowp vec2 inUV;

	uniform highp mat4 MVPMatrix;
	
	varying lowp vec2 vTexCoord;

	void main(void)
	{	
		gl_Position = MVPMatrix * inVertex;
		vTexCoord 	= inUV;
	}
	[/GLSL]
[/VERTEXSHADER]

[FRAGMENTSHADER]
	[GLSL]
	uniform sampler2D sTexture;
	varying lowp vec2 vTexCoord;
	
	void main()
	{
		gl_FragColor = texture2D(sTexture, vTexCoord);
	}
	[/GLSL]
[/FRAGMENTSHADER]
