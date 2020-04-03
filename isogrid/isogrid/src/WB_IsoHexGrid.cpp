#include "WB_IsoHexGrid.h"
#include "typedef.h"
#include <cmath>

vec<int> WB_IsoHexGrid::next = { 1, 2, 3, 4, 5, 0 };
int WB_IsoHexGrid::c = 24;

double WB_IsoHexGrid::oh = 0.5;
double WB_IsoHexGrid::ot = 1.0 / 3.0;
double WB_IsoHexGrid::tt = 1.0 - ot;
vec<double> WB_IsoHexGrid::vertexOffsets = { 1,  0,   1,  1,   0,   1,   -1,  0,   -1,  -1,  0,   -1, 1,
	                                         oh, oh,  1,  -oh, oh,  -1,  -oh, -oh, -1,  oh,  -oh, oh, 0,
	                                         oh, oh,  0,  oh,  -oh, 0,   -oh, -oh, 0,   -oh, tt,  ot, ot,
	                                         tt, -ot, ot, -tt, -ot, -ot, -tt, ot,  -ot, 0,   0 };

vec<int> WB_IsoHexGrid::mapFragmentsFromPosOne = { 26, 27, 28, 29, 24, 25, 22, 23, 18, 19, 20, 21, 2,  3,  4, 5, 0, 1,
	                                               34, 35, 30, 31, 32, 33, 14, 15, 16, 17, 12, 13, 10, 11, 6, 7, 8, 9 };
vec<int> WB_IsoHexGrid::mapQFromPosOne = { 1,  1,  1,  1,  1,  1,  1, 1, 1, 1, 1, 1, -1, -1, -1, -1, -1, -1,
	                                       -1, -1, -1, -1, -1, -1, 0, 0, 0, 0, 0, 0, 0,  0,  0,  0,  0,  0 };
vec<int> WB_IsoHexGrid::mapRFromPosOne = { 1, 1, 1, 1, 1, 1, 1,  1,  1,  1,  1,  1,  0,  0,  0,  0,  0,  0,
	                                       0, 0, 0, 0, 0, 0, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 };
vec<int> WB_IsoHexGrid::mapFragmentsFromNegOne = { 16, 17, 12, 13, 14, 15, 32, 33, 34, 35, 30, 31,
	                                               28, 29, 24, 25, 26, 27, 8,  9,  10, 11, 6,  7,
	                                               4,  5,  0,  1,  2,  3,  20, 21, 22, 23, 18, 19 };
vec<int> WB_IsoHexGrid::mapQFromNegOne = { 1,  1,  1,  1,  1,  1,  0,  0,  0,  0,  0,  0,  0, 0, 0, 0, 0, 0,
	                                       -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 1, 1, 1, 1, 1, 1 };
vec<int> WB_IsoHexGrid::mapRFromNegOne = { 0,  0,  0,  0,  0,  0,  1,  1,  1,  1,  1,  1,  1, 1, 1, 1, 1, 1,
	                                       -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 0, 0, 0, 0, 0, 0 };
vec<vec<int>> WB_IsoHexGrid::fragmentVertices = {
	{ 18, 0, 6 },  { 18, 6, 1 },  { 18, 1, 13 }, { 18, 13, c }, { 18, c, 12 }, { 18, 12, 0 },
	{ 19, 1, 7 },  { 19, 7, 2 },  { 19, 2, 14 }, { 19, 14, c }, { 19, c, 13 }, { 19, 13, 1 },
	{ 20, 2, 8 },  { 20, 8, 3 },  { 20, 3, 15 }, { 20, 15, c }, { 20, c, 14 }, { 20, 14, 2 },
	{ 21, 3, 9 },  { 21, 9, 4 },  { 21, 4, 16 }, { 21, 16, c }, { 21, c, 15 }, { 21, 15, 3 },
	{ 22, 4, 10 }, { 22, 10, 5 }, { 22, 5, 17 }, { 22, 17, c }, { 22, c, 16 }, { 22, 16, 4 },
	{ 23, 5, 11 }, { 23, 11, 0 }, { 23, 0, 12 }, { 23, 12, c }, { 23, c, 17 }, { 23, 17, 5 }
};
#ifndef M_PI
#define M_PI 3.14159265358979323846264338327950288
#endif
double WB_IsoHexGrid::c60 = std::cos(M_PI / 3.0);
double WB_IsoHexGrid::s60 = std::sin(M_PI / 3.0);
vec<vec<int>> WB_IsoHexGrid::neighborHexes = { { 2, 1 }, { 1, 2 }, { -1, 1 }, { -2, -1 }, { -1, -2 }, { 1, -1 } };

vec<int> WB_IsoHexGrid::interHexNeighbor = { 19, 18, -1, -1, -1, -1, 25, 24, -1, -1, -1, -1, 31, 30, -1, -1, -1, -1,
	                                         1,  0,  -1, -1, -1, -1, 7,  6,  -1, -1, -1, -1, 13, 12, -1, -1, -1, -1 };
vec<int> WB_IsoHexGrid::interHexSegment = { 0,  6,  6,  1,  -1, -1, -1, -1, -1, -1, -1, -1, 1,  7,  7,  2,  -1, -1,
	                                        -1, -1, -1, -1, -1, -1, 2,  8,  8,  3,  -1, -1, -1, -1, -1, -1, -1, -1,
	                                        3,  9,  9,  4,  -1, -1, -1, -1, -1, -1, -1, -1, 4,  10, 10, 5,  -1, -1,
	                                        -1, -1, -1, -1, -1, -1, 5,  11, 11, 0,  -1, -1, -1, -1, -1, -1, -1, -1 };
vec<int> WB_IsoHexGrid::interHexNeighborQ = { +2, +2, 0, 0, 0, 0, +1, +1, 0, 0, 0, 0, -1, -1, 0, 0, 0, 0,
	                                          -2, -2, 0, 0, 0, 0, -1, -1, 0, 0, 0, 0, 1,  1,  0, 0, 0, 0 };
vec<int> WB_IsoHexGrid::interHexNeighborR = { +1, +1, 0, 0, 0, 0, +2, +2, 0, 0, 0, 0, 1,  1,  0, 0, 0, 0,
	                                          -1, -1, 0, 0, 0, 0, -2, -2, 0, 0, 0, 0, -1, -1, 0, 0, 0, 0 };

#include "WB_IsoGridCell.h"
#include "WB_IsoGridLine.h"
#include "WB_IsoGridSegment.h"

void WB_IsoHexGrid::addSegment(double q, double r, int i1, int i2)
{
	WB_IsoGridSegment segment; 
	segment.initialize(
	    (int)std::round(6 * (q + vertexOffsets[2 * i1])), (int)std::round(6 * (r + vertexOffsets[2 * i1 + 1])),
	    (int)std::round(6 * (q + vertexOffsets[2 * i2])), (int)std::round(6 * (r + vertexOffsets[2 * i2 + 1])));
	long key = segment.getHash();
	WB_IsoGridLine *line = getLineFromMap(key);
	if (line == nullptr)
	{
		auto idx = linesMemory.size();
		linesMemory.resize(idx + 1);
		line = &linesMemory.back();
		line->type = segment.getType();
		line->lineValue = segment.getLineValue();

		linesMap.insert({ key, idx });
	}
	line->add(segment);
}

void WB_IsoHexGrid::clearFragment(int q, int r, int s)
{
	long key = getCellHash(q, r);
	if (cells.find(key) == cells.end())
	{
		return;
	}
	WB_IsoGridCell *cell = cell_(cells[key]);
	;
	if (cell == nullptr)
	{
		return;
	}
	cell->colorIndices[s] = 0;
	cell->labels[s] = -1;
	cell->z[s] = -INT_MAX;
	cell->cubei[s] = -INT_MAX;
	cell->cubej[s] = -INT_MAX;
	cell->cubek[s] = -INT_MAX;
	if (cell->isEmpty())
	{
		cells.erase(key);
	}
}

void WB_IsoHexGrid::collectInterHexSegments()
{
	WB_IsoGridCell *neighbor;
	int z = 0, label = 0, colorIndex = 0;
	long hash = 0, nhash = 0;

	for (auto &item : cells)
	{
		auto cell = cell_(item.second);
		hash = getCellHash(cell->getQ(), cell->getR());
		for (int i = 0; i < 36; i++)
		{
			if (cell->getLabel(i) >= 0)
			{
				if (interHexNeighbor[i] >= 0)
				{
					neighbor = getNeighbor(cell->getQ(), cell->getR(), i);
					if (neighbor == nullptr)
					{
						addSegment(cell->getQ(), cell->getR(), interHexSegment[2 * i], interHexSegment[2 * i + 1]);
					}
					else
					{
						nhash = getCellHash(cell->getQ() + interHexNeighborQ[i], cell->getR() + interHexNeighborR[i]);
						label = neighbor->getLabel(interHexNeighbor[i]);
						if (nhash < hash || label == -1)
						{

							z = neighbor->getZ(interHexNeighbor[i]);
							colorIndex = neighbor->getColorIndex(interHexNeighbor[i]);
							if (areSeparate(label, cell->getLabel(i), colorIndex, cell->getColorIndex(i), cell->getZ(i),
							                z))
							{
								addSegment(cell->getQ(), cell->getR(), interHexSegment[2 * i],
								           interHexSegment[2 * i + 1]);
							}
						}
					}
				}
			}
		}
	}
}

void WB_IsoHexGrid::collectLines()
{
	linesMap.clear();
	collectInterHexSegments();
	collectInterTriangleSegments();
	collectIntraTriangleSegments();

	lines.clear();
	for (auto &item : linesMap)
	{
		lines.push_back(item.second);
	}

	auto comp = [this](const int &arg0_, const int &arg1_) -> bool {
		auto arg0 = line_(arg0_);
		auto arg1 = line_(arg1_);
		if (arg0->type < arg1->type)
		{
			return true; //-1;
		}
		else if (arg0->type > arg1->type)
		{
			return false;
		}
		else if (arg0->lineValue < arg1->lineValue)
		{
			return true;
		}
		else if (arg0->lineValue > arg1->lineValue)
		{
			return false;
		}
		return false;
	};

	std::sort(lines.begin(), lines.end(), comp);
	// lines.sort(new WB_IsoGridLine.HexLineSort());
	int i = 0;
	for (auto &lineidx : lines)
	{
		auto line = line_(lineidx);

		line->sort();
		line->optimize();
		if (i % 2 == 0)
			line->reverse();
		i++;
	}
}

vec<int> WB_IsoHexGrid::interTriangleNeighbor = {
	-1, -1, 11, 10, 33, 32, -1, -1, 17, 16, 3,  2,  -1, -1, 23, 22, 9,  8,
	-1, -1, 29, 28, 15, 14, -1, -1, 35, 34, 21, 20, -1, -1, 5,  4,  27, 26
};
vec<int> WB_IsoHexGrid::interTriangleSegment = {
	-1, -1, -1, -1, 1, 13, 13, c, c, 12, 12, 0, -1, -1, -1, -1, 2, 14, 14, c, c, 13, 13, 1,
	-1, -1, -1, -1, 3, 15, 15, c, c, 14, 14, 2, -1, -1, -1, -1, 4, 16, 16, c, c, 15, 15, 3,
	-1, -1, -1, -1, 5, 17, 17, c, c, 16, 16, 4, -1, -1, -1, -1, 0, 12, 12, c, c, 17, 17, 5
};

void WB_IsoHexGrid::collectInterTriangleSegments()
{
	int z = 0, label = 0, colorIndex = 0;
	for (auto &item : cells)
	{
		auto cell = cell_(item.second);
		for (int i = 0; i < 36; i++)
		{
			if (interTriangleNeighbor[i] > i)
			{
				label = cell->getLabel(interTriangleNeighbor[i]);
				z = cell->getZ(interTriangleNeighbor[i]);
				colorIndex = cell->getColorIndex(interTriangleNeighbor[i]);
				if (areSeparate(label, cell->getLabel(i), colorIndex, cell->getColorIndex(i), cell->getZ(i), z))
				{
					addSegment(cell->getQ(), cell->getR(), interTriangleSegment[2 * i],
					           interTriangleSegment[2 * i + 1]);
				}
			}
		}
	}
}

vec<int> WB_IsoHexGrid::intraTriangleNeighbor = { 1,  2,  3,  4,  5,  0,  7,  8,  9,  10, 11, 6,
	                                              13, 14, 15, 16, 17, 12, 19, 20, 21, 22, 23, 18,
	                                              25, 26, 27, 28, 29, 24, 31, 32, 33, 34, 35, 30 };
vec<int> WB_IsoHexGrid::intraTriangleSegment = { 18, 6, 18, 1,  18, 13, 18, c,  18, 12, 18, 0,  19, 7,  19, 2,  19, 14,
	                                             19, c, 19, 13, 19, 1,  20, 8,  20, 3,  20, 15, 20, c,  20, 14, 20, 2,
	                                             21, 9, 21, 4,  21, 16, 21, c,  21, 15, 21, 3,  22, 10, 22, 5,  22, 17,
	                                             22, c, 22, 16, 22, 4,  23, 11, 23, 0,  23, 12, 23, c,  23, 17, 23, 5 };

void WB_IsoHexGrid::collectIntraTriangleSegments()
{
	int z = 0, label = 0, colorIndex = 0;
	for (auto &item : cells)
	{
		WB_IsoGridCell *cell = cell_(item.second);
		for (int i = 0; i < 36; i++)
		{

			label = cell->getLabel(intraTriangleNeighbor[i]);
			z = cell->getZ(intraTriangleNeighbor[i]);
			colorIndex = cell->getColorIndex(intraTriangleNeighbor[i]);
			if (areSeparate(label, cell->getLabel(i), colorIndex, cell->getColorIndex(i), cell->getZ(i), z))
			{
				addSegment(cell->getQ(), cell->getR(), intraTriangleSegment[2 * i], intraTriangleSegment[2 * i + 1]);
			}
		}
	}
}

#include "applet.h"

void WB_IsoHexGrid::drawLines(PApplet *home)
{
	for (auto &lineidx : lines)
	{
		auto line = line_(lineidx);
		for (auto &segment : *line->getSegments())
		{
			home->line((float)(segment.getQ1() / 6.0 * s60 * size[0] + origin[0]),
			           (float)((segment.getR1() - segment.getQ1() * c60) / 6.0 * size[1] + origin[1]),
			           (float)((segment.getQ2() / 6.0 * s60 * size[0]) + origin[0]),
			           (float)((segment.getR2() - segment.getQ2() * c60) / 6.0 * size[1] + origin[1]));
		}
	}
}

// "Add" is conditional and only overwrites if its z-value is higher than
// current values
void WB_IsoHexGrid::addFragment(int q, int r, int s, int z, int label, int colorIndex, int i, int j, int k)
{
	long key = getCellHash(q, r);
	WB_IsoGridCell *cell = getCell(key); // cells.get(key);
	bool constructorCalled = false;

	if (cell == nullptr)
	{
		auto index = cellsMemory.size();
		cellsMemory.push_back(WB_IsoGridCell());
		cell = &cellsMemory.back();
		cell->q = q;
		cell->r = r;
		cell->initCell();
		cells.insert({ key, index });
		constructorCalled = true;
		;
	}

	if (z > cell->z[s])
	{
		cell->labels[s] = label;
		cell->z[s] = z;
		cell->colorIndices[s] = colorIndex;
		cell->cubei[s] = i;
		cell->cubej[s] = j;
		cell->cubek[s] = k;
	}
}

WB_IsoGridCell *WB_IsoHexGrid::getCell(long key)
{
	if (cells.find(key) == cells.end())
	{
		return nullptr;
	}
	return &cellsMemory[cells[key]];
}

void WB_IsoHexGrid::drawFragments(PApplet *home, vec<int> &colors, int zmin, int zmax, int znear, int zfar, int mini,
                                  int maxi, int minj, int maxj, int mink, int maxk)
{
	vec<double> center;
	for (auto &item : cells)
	{
		WB_IsoGridCell *cell = cell_(item.second);
		center = gridCoordinates(cell->getQ(), cell->getR());
		for (int f = 0; f < 36; f++)
		{
			if (cell->labels[f] > -1 && cell->z[f] >= zmin && cell->z[f] < zmax && cell->cubei[f] >= mini &&
			    cell->cubei[f] < maxi && cell->cubej[f] >= minj && cell->cubej[f] < maxj && cell->cubek[f] >= mink &&
			    cell->cubek[f] < maxk)
			{
				home->fill(home->makeColor(colors[10 * cell->colorIndices[f] + cell->labels[f]],
				                           (cell->colorIndices[f] == 0) ? cell->z[f] : znear, zfar, znear));
				home->beginShape(PConstants::TRIANGLES);
				vertex(home, center[0] + offsets[2 * fragmentVertices[f][0]] * size[0],
				       center[1] + offsets[2 * fragmentVertices[f][0] + 1] * size[1]);
				vertex(home, center[0] + offsets[2 * fragmentVertices[f][1]] * size[0],
				       center[1] + offsets[2 * fragmentVertices[f][1] + 1] * size[1]);
				vertex(home, center[0] + offsets[2 * fragmentVertices[f][2]] * size[0],
				       center[1] + offsets[2 * fragmentVertices[f][2] + 1] * size[1]);

				home->endShape();
			}
		}
	}
}

void WB_IsoHexGrid::drawFragments(PApplet *home, vec<int> &colors, int zmin, int zmax)
{
	vec<double> center;
	for (auto &item : cells)
	{
		WB_IsoGridCell *cell = cell_(item.second);
		center = gridCoordinates(cell->getQ(), cell->getR());
		for (int f = 0; f < 36; f++)
		{
			if (cell->labels[f] > -1 && cell->z[f] >= zmin && cell->z[f] < zmax)
			{

				home->fill(colors[10 * cell->colorIndices[f] + cell->labels[f]]);
				home->beginShape(PConstants::TRIANGLES);
				vertex(home, center[0] + offsets[2 * fragmentVertices[f][0]] * size[0],
				       center[1] + offsets[2 * fragmentVertices[f][0] + 1] * size[1]);
				vertex(home, center[0] + offsets[2 * fragmentVertices[f][1]] * size[0],
				       center[1] + offsets[2 * fragmentVertices[f][1] + 1] * size[1]);
				vertex(home, center[0] + offsets[2 * fragmentVertices[f][2]] * size[0],
				       center[1] + offsets[2 * fragmentVertices[f][2] + 1] * size[1]);

				home->endShape();
			}
		}
	}
}

void WB_IsoHexGrid::drawFragments(PApplet *home, int zmin, int zmax)
{
	vec<double> center;
	for (auto &item : cells)
	{
		WB_IsoGridCell *cell = cell_(item.second);
		center = gridCoordinates(cell->getQ(), cell->getR());
		for (int f = 0; f < 36; f++)
		{
			if (cell->labels[f] > -1 && cell->z[f] >= zmin && cell->z[f] < zmax)
			{
				home->beginShape(PConstants::TRIANGLES);
				vertex(home, center[0] + offsets[2 * fragmentVertices[f][0]] * size[0],
				       center[1] + offsets[2 * fragmentVertices[f][0] + 1] * size[1]);
				vertex(home, center[0] + offsets[2 * fragmentVertices[f][1]] * size[0],
				       center[1] + offsets[2 * fragmentVertices[f][1] + 1] * size[1]);
				vertex(home, center[0] + offsets[2 * fragmentVertices[f][2]] * size[0],
				       center[1] + offsets[2 * fragmentVertices[f][2] + 1] * size[1]);

				home->endShape();
			}
		}
	}
}

void WB_IsoHexGrid::drawFragments(PApplet *home)
{
	vec<double> center;
	for (auto &item : cells)
	{
		WB_IsoGridCell *cell = cell_(item.second);
		center = gridCoordinates(cell->getQ(), cell->getR());
		for (int f = 0; f < 36; f++)
		{
			if (cell->labels[f] > -1)
			{
				home->beginShape(PConstants::TRIANGLES);
				vertex(home, center[0] + offsets[2 * fragmentVertices[f][0]] * size[0],
				       center[1] + offsets[2 * fragmentVertices[f][0] + 1] * size[1]);
				vertex(home, center[0] + offsets[2 * fragmentVertices[f][1]] * size[0],
				       center[1] + offsets[2 * fragmentVertices[f][1] + 1] * size[1]);
				vertex(home, center[0] + offsets[2 * fragmentVertices[f][2]] * size[0],
				       center[1] + offsets[2 * fragmentVertices[f][2] + 1] * size[1]);

				home->endShape();
			}
		}
	}
}

void WB_IsoHexGrid::drawFragments(PApplet *home, vec<int> &colors)
{
	vec<double> center;
	for (auto &item : cells)
	{
		WB_IsoGridCell *cell = cell_(item.second);
		center = gridCoordinates(cell->getQ(), cell->getR());
		for (int f = 0; f < 36; f++)
		{
			if (cell->labels[f] > -1)
			{

				home->fill(colors[10 * cell->colorIndices[f] + cell->labels[f]]);
				home->beginShape(PConstants::TRIANGLES);
				vertex(home, center[0] + offsets[2 * fragmentVertices[f][0]] * size[0],
				       center[1] + offsets[2 * fragmentVertices[f][0] + 1] * size[1]);
				vertex(home, center[0] + offsets[2 * fragmentVertices[f][1]] * size[0],
				       center[1] + offsets[2 * fragmentVertices[f][1] + 1] * size[1]);
				vertex(home, center[0] + offsets[2 * fragmentVertices[f][2]] * size[0],
				       center[1] + offsets[2 * fragmentVertices[f][2] + 1] * size[1]);

				home->endShape();
			}
		}
	}
}

void WB_IsoHexGrid::vertex(PApplet *home, double px, double py)
{
	home->vertex((float)px, (float)py);
}
