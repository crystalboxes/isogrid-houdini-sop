#include "applet.h"
//
#include "noise.h"

PerlinNoise perlin;

void PApplet::noiseSeed(long long seed)
{
	perlin = PerlinNoise((uint32_t)seed);
}

float PApplet::noise(float x, float y, float z)
{
	return perlin.noise(x, y, z);
}

void PApplet::noFill()
{
}

int PApplet::makeColor(float x, float y, float z)
{
	return ((int)(x / 255) << 16) + ((int)(y / 255) << 8) + ((int)(z / 255));
}

int PApplet::makeColor(float x, float y, float z, float a)
{
	return ((int)(a / 255) << 24) + //
	       ((int)(x / 255) << 16) + //
	       ((int)(y / 255) << 8) + //
	       ((int)(z / 255));
}

void PApplet::fill(int x)
{
}

void PApplet::ortho()
{
}

void PApplet::pushMatrix()
{
}

void PApplet::noStroke()
{
}

void PApplet::popMatrix()
{
}

PrintWriter PApplet::createWriter(const String &name)
{
	return { name };
}

void PApplet::fullScreen(int a)
{
}

void PApplet::smooth(int w)
{
}
void PApplet::stroke_(int w)
{
}
void PApplet::strokeWeight(float w)
{
}
void PApplet::noCursor()
{
}

float random(float v)
{
	return rand() * v / static_cast<float>(RAND_MAX);
}
void randomSeed(long long seed)
{
	srand((uint32_t)seed);
}

float PApplet::random(float v)
{
	return ::random(v);
}

void PApplet::randomSeed(long long seed)
{
	return ::randomSeed(seed);
}

float PApplet::constrain(float x, float m, float mx)
{
	return x > mx ? mx : x < m ? m : x;
}

void PApplet::save(const std::string &str)
{
}

void PApplet::text(const std::string &str, int x, int y)
{
}

void PApplet::println(const std::string &str)
{
	if (outputToConsole)
	{
		std::cout << str;
	}
	else
	{
		std_out += str;
	}
}

void PApplet::beginRecord(const std::string &str1, const std::string &str2)
{
	println(str1);
}
void PApplet::endRecord()
{
	println("endRecord");
}

void PApplet::rotate(float rad)
{
}

float PApplet::radians(float degrees)
{
	return degrees * 3.1415926535897931f / 180.f;
}
void PApplet::scale_(float x, float y)
{
}

void PApplet::background(int x)
{
}

void PApplet::translate(float x, float y)
{
}
