 [EFFECT] 
	NAME    ShaderGUI

	ATTRIBUTE inVertex				POSITION
	ATTRIBUTE inColor				VERTEXCOLOR

	UNIFORM MVPMatrix			WORLDVIEWPROJECTION
	UNIFORM sTexture				TEXTURE0
	
	RENDERQUEUE					10000
	RENDERTYPE						Transparent
	BLENDING							SrcAlpha OneMinusSrcAlpha
	ZTEST									Always
	ZWRITE								Off
	FACECULL							Off
[/EFFECT]

[VERTEXSHADER]
	attribute highp vec4 inVertex;
	attribute lowp vec4 inColor;

	uniform highp mat4 MVPMatrix;
	
	varying lowp vec4 vColor;

	void main(void)
	{	
		gl_Position = MVPMatrix * inVertex;
		vColor 	= inColor;
	}
[/VERTEXSHADER]

[FRAGMENTSHADER]
	uniform sampler2D sTexture;
	varying lowp vec4 vColor;
	
	void main()
	{
		gl_FragColor = vColor;
	}
[/FRAGMENTSHADER]
