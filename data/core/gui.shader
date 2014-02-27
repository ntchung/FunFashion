 [EFFECT] 
	NAME    ShaderGUI

	ATTRIBUTE inVertex				POSITION
	ATTRIBUTE inUV					UV0

	UNIFORM MVPMatrix			WORLDVIEWPROJECTION
	UNIFORM sTexture				TEXTURE0
	
	RENDERQUEUE					Geometry+10
	BLENDING							SrcAlpha OneMinusSrcAlpha
	ZTEST									Always
	ZWRITE								Off
	FACECULL							Off
[/EFFECT]

[VERTEXSHADER]
	attribute highp vec4 inVertex;
	attribute lowp vec2 inUV;

	uniform highp mat4 MVPMatrix;
	
	varying lowp vec2 vTexCoord;

	void main(void)
	{	
		gl_Position = MVPMatrix * inVertex;
		vTexCoord 	= inUV;
	}
[/VERTEXSHADER]

[FRAGMENTSHADER]
	uniform sampler2D sTexture;
	varying lowp vec2 vTexCoord;
	
	void main()
	{
		gl_FragColor = texture2D(sTexture, vTexCoord);
	}
[/FRAGMENTSHADER]
