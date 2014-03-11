#include "stdafx.h"
#include "FashionGame.h"
#include "Resources.h"
#include "Shader.h"
#include "Material.h"
#include "PictureRenderer.h"
#include "RenderTexture.h"
#include "gui/GUI.h"

static StatePlay* g_statePlayInstance = 0;
static unsigned char* g_backgroundBitmap;
static int g_backgroundWidth;
static int g_backgroundHeight;
static bool g_hasBackgroundChanged;

StatePlay* StatePlay::instance()
{
	if (!g_statePlayInstance)
	{
		g_statePlayInstance = new StatePlay();
	}

	return g_statePlayInstance;
}

void StatePlay::destroy()
{
	delete this;
}

StatePlay::StatePlay()
: m_isInitialized(false)
{
}

StatePlay::~StatePlay()
{
	delete[] g_backgroundBitmap;
	m_pictureRenderer->release();
	m_rtRenderer->release();
}

void StatePlay::begin()
{
	if (!m_isInitialized)
	{
		m_isInitialized = true;

		m_backgroundPicture = Texture::create(BACKGROUND_WIDTH, BACKGROUND_HEIGHT);
		g_backgroundBitmap = new unsigned char[BACKGROUND_WIDTH * BACKGROUND_HEIGHT * 4];
		memset(g_backgroundBitmap, 0xFF, BACKGROUND_WIDTH * BACKGROUND_HEIGHT * 4);
		/*for (int i = 0; i < 1024 * 256; ++i)
		{
			g_backgroundBitmap[i * 4 + 0] = 0xFF;
			g_backgroundBitmap[i * 4 + 1] = 0;
			g_backgroundBitmap[i * 4 + 2] = 0;
			g_backgroundBitmap[i * 4 + 3] = 0xFF;
		}*/

		g_backgroundWidth = g_backgroundHeight = 0;
		m_backgroundPicture->setData(g_backgroundBitmap);
		g_hasBackgroundChanged = false;

		Shader* shader = Resources::shared()->load<Shader>("flat.shader");
		Material* material = Material::create(0, shader);		
		m_pictureRenderer = PictureRenderer::create();
		m_pictureRenderer->setMaterial(material);
		material->setTexture(0, m_backgroundPicture);		

		Material* rtMaterial = Material::create(1, shader);
		rtMaterial->setTexture(0, (Texture*)rtCamera()->renderTexture());
		m_rtRenderer = PictureRenderer::create();
		m_rtRenderer->setMaterial(rtMaterial);

		Shader* transShader = Resources::shared()->load<Shader>("transparent.shader");
		Material* shirtMaterial = Material::create(2, transShader);
		shirtMaterial->setTexture(0, Resources::shared()->load<Texture>("testshirt.pvr"));
		m_shirtRenderer = PictureRenderer::create();
		m_shirtRenderer->setMaterial(shirtMaterial);
	}
}

void StatePlay::end()
{

}

void StatePlay::update()
{
	if (g_hasBackgroundChanged)
	{
		g_hasBackgroundChanged = false;
		m_backgroundPicture->setData(g_backgroundBitmap);
	}

#ifdef WIN32
	if ((GetAsyncKeyState(VK_F1) & 0x8000) == 0x8000)
	{
		gameRequestScreenshot("E:\\test.tga");
	}
#endif
}

void StatePlay::render()
{
	m_shirtRenderer->reset();
	m_shirtRenderer->draw(rtCamera(), 0, 0, 4, 4);

	m_pictureRenderer->reset();
	m_pictureRenderer->draw(rtCamera(), 0, 0, 8.0f, 8.0f);

	m_rtRenderer->reset();
	m_rtRenderer->draw(camera(), 0, 0, 8.0f, 8.0f);
}

void StatePlay::onGUI()
{
}

void StatePlay::setRotateRight(bool value)
{
	m_pictureRenderer->setRotateRight(value);
}

void gameTakeScreenshot()
{
	if (g_backgroundWidth <= 0 || g_backgroundHeight <= 0)
	{
		return;
	}

	RenderTexture* rt = rtCamera()->renderTexture();
	rt->begin();

	glReadPixels(0, 0, BACKGROUND_WIDTH, BACKGROUND_HEIGHT, GL_RGBA, GL_UNSIGNED_BYTE, g_backgroundBitmap);

	rt->end();
}

void gameSetBackgroundPicture(int* pixels, int width, int height)
{
	memset(g_backgroundBitmap, 0xFF, BACKGROUND_WIDTH * BACKGROUND_HEIGHT * 4);

	int newWidth = BACKGROUND_WIDTH;
	int newHeight = BACKGROUND_HEIGHT;
	if (width < height)
	{
		newWidth = (width * newHeight) / height;
		StatePlay::instance()->setRotateRight(false);

		g_backgroundWidth = newWidth;
		g_backgroundHeight = newHeight;
	}
	else
	{
		newHeight = (height * newWidth) / width;
		StatePlay::instance()->setRotateRight(true);

		g_backgroundWidth = newHeight;
		g_backgroundHeight = newWidth;
	}	

	int xStart = (BACKGROUND_WIDTH - newWidth) >> 1;
	int yStart = (BACKGROUND_HEIGHT - newHeight) >> 1;

	const int xRatio = ((width - 1) << 8) / newWidth;
	const int yRatio = ((height - 1) << 8) / newHeight;
	int x, y;
	int xDiff, yDiff;
	int ixDiff, iyDiff;
	int a, b, c, d;
	int m, n, o, p;
	int red, green, blue;

	int i, j;
	for (i = 0; i < newHeight; ++i)
	{
		yDiff = yRatio * i;
		y = ((unsigned int)yDiff >> 8);
		yDiff -= (y << 8);

		int* originalRgb = pixels + (y * width);
		int* scaledRgb = (int*)(g_backgroundBitmap + (((i + yStart) * BACKGROUND_WIDTH) * 4));

		for (j = 0; j < newWidth; ++j) {
			xDiff = xRatio * j;
			x = ((unsigned int)xDiff >> 8);
			xDiff -= (x << 8);

			a = originalRgb[x];
			b = originalRgb[x + 1];
			c = originalRgb[x + width];
			d = originalRgb[x + width + 1];

			ixDiff = (256 - xDiff);
			iyDiff = (256 - yDiff);
			m = ((unsigned int)(ixDiff * iyDiff)) >> 8;
			n = ((unsigned int)(xDiff * iyDiff)) >> 8;
			o = ((unsigned int)(yDiff * ixDiff)) >> 8;
			p = ((unsigned int)(xDiff * yDiff)) >> 8;

			red = ((unsigned int)((((((a)& 0xff0000) * m))
				+ ((((b)& 0xff0000) * n))
				+ ((((c)& 0xff0000) * o))
				+ ((((d)& 0xff0000) * p))))) >> 24
				;

			green = ((unsigned int)(((((a & 0xff00) * m))
				+ (((b & 0xff00) * n))
				+ (((c & 0xff00) * o))
				+ (((d & 0xff00) * p))))) >> 16
				;

			blue = ((unsigned int)(((((a & 0xff) * m))
				+ (((b & 0xff) * n))
				+ (((c & 0xff) * o))
				+ (((d & 0xff) * p))))) >> 8
				;

			scaledRgb[j + xStart] =
				(blue << 16) & 0xff0000 |
				(green << 8) & 0xff00 |
				red;
		}
	}

	g_hasBackgroundChanged = true;
}

void gameWriteScreenShotTGA(const char* path)
{
	if (g_backgroundWidth <= 0 || g_backgroundHeight <= 0)
	{
		return;
	}

	int width = g_backgroundWidth;
	int height = g_backgroundHeight;

	FILE* fp = fopen(path, "wb");

	// Type
	fputc(0x00, fp);
	fputc(0x00, fp);
	fputc(0x02, fp);
	fputc(0x00, fp);
	
	fputc(0x00, fp);
	fputc(0x00, fp);
	fputc(0x00, fp);
	fputc(0x00, fp);

	fputc(0x00, fp);
	fputc(0x00, fp);
	fputc(0x00, fp);
	fputc(0x00, fp);

	fputc(width & 0xFF, fp);
	fputc((width >> 8) & 0xFF, fp);
	fputc(height & 0xFF, fp);
	fputc((height >> 8) & 0xFF, fp);
	fputc(0x18, fp);
	fputc(0x00, fp);

	int x1 = (BACKGROUND_WIDTH - width) >> 1;
	int x2 = BACKGROUND_WIDTH - x1;
	int y1 = (BACKGROUND_HEIGHT - height) >> 1;
	int y2 = BACKGROUND_HEIGHT - y1;

	for (int y = y2 - 1; y >= y1; --y)
	{
		int n = ( y * BACKGROUND_WIDTH + x1 ) * 4;
		for (int x = 0; x < width; ++x)
		{
			fputc(g_backgroundBitmap[n + 2], fp);
			fputc(g_backgroundBitmap[n + 1], fp);
			fputc(g_backgroundBitmap[n + 0], fp);
			n += 4;
		}
	}

	fclose(fp);
}
