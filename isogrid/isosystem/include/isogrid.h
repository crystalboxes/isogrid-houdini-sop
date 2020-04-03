#pragma once
#include <functional>
#include <string>
#include <vector>

enum class Commands : char
{
	ResetSameNoiseSeed = 'n',
	ResetNewNoiseSeed = 'N',
	RotateCW = 'q',
	RotateCCW = 'e',
	ShiftUp = 'w',
	ShiftDown = 's',
	ShiftLeft = 'a',
	ShiftRight = 'd',
	ToggleShading = 'f',
	Darken = 'z',
	Lighten = 'c',
	ToggleGUI = 'g',
	ToggleDualRender = 'j',
	RemoveBlock1 = '1',
	RemoveBlock2 = '2',
	RemoveBlock3 = '3',
	RemoveBlock4 = '4',
	RemoveBlock5 = '5',
	RemoveBlock6 = '6',
	RemoveBlock7 = '7',
	RemoveBlocksRandom = '8',
	Maze = '9',
	PerlinNoise = '0',
	PerlinColorNoise = '/',
	PerlinNoise2 = '?',
	Invert = 'x',
	EdgeTransform = 'R',
	RandomSelectionEdgeTransform = 'r',
	WireTransform = 'T',
	RandomSelectionWireTransform = 't',
	Hollow = 'H',
	RandomSelectionHollow = 'h',
	SliceIDirection = 'm',
	RandomSelectionSliceIDirection = 'M',
	SliceJDirection = '<',
	RandomSelectionSliceJDirection = ',',
	SliceKDirection = '>',
	RandomSelectionSliceKDirection = '.',
	RotateIAxis = 'k',
	RotateJAxis = 'l',
	RotateKAxis = ';',
	Flip = 'y',
	MirrorIPlane = 'u',
	MirrorJPlane = 'i',
	MirrorLPlane = 'o',
	MirrorIKPlane = 'p'
};

struct IsoGridInstance
{
	IsoGridInstance();
	~IsoGridInstance();

	void init();
	void allocate();
	void doOperation(char key);
	void setInitResolution(int res);

	const char *getConsoleOutput();

	struct Face
	{
		int a, b, c, d;
	};
	struct Vertex
	{
		float x, y, z;
	};

	void getMesh(std::function<void(float, float, float)> addVertexCallback,
	             std::function<void(int, int, int, int)> addFaceCallback);

	void executeCommands(const std::string &commands);
	void executeCommands(const std::vector<Commands> &commands);

private:
	int initialResolution = 16;
	struct PIsoApplet *applet = nullptr;
};
