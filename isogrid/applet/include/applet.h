#pragma once
#include <iostream>
#include <stdlib.h>
#include <string>

#include "typedef.h"

struct PrintWriter
{
	String name;
	void println(const String &val)
	{
	}
	void flush()
	{
	}
	void close()
	{
	}
};

#define P3D 0

enum class PConstants : uint8_t
{
	TRIANGLES
};

float random(float v);
void randomSeed(long long seed);

struct PApplet
{

	void beginShape(PConstants c)
	{
	}
	void endShape()
	{
	}
	void vertex(float x, float y)
	{
	}

	void line(float x, float y, float z, float w)
	{
	}

	void fullScreen(int a);
	void smooth(int w);
	void noCursor();
	float constrain(float x, float m, float mx);
	void println(const std::string &str);

	void noiseSeed(long long seed);
	float noise(float x, float y, float z);

	float random(float v);
	void randomSeed(long long seed);

	void stroke_(int w);
	void strokeWeight(float w);
	void save(const std::string &str);
	void beginRecord(const std::string &str1, const std::string &str2);
	void endRecord();
	void rotate(float rad);
	float radians(float x);
	void scale_(float x, float y);
	void background(int x);
	void translate(float x, float y);
	PrintWriter createWriter(const String &name);
	int makeColor(float x, float y, float z, float a);
	int makeColor(float x, float y, float z);
	void fill(int x);

	void ortho();
	void pushMatrix();
	void noStroke();
	void popMatrix();
	void text(const std::string &str, int x, int y);
	void noFill();

	bool outputToConsole = true;

	std::string std_out;
};
