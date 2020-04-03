#include "WB_IsoGridCell.h"

void WB_IsoGridCell::initCell()
{
	auto &cell = *this;

	cell.labels.resize(36);
	cell.colorIndices.resize(36);
	cell.z.resize(36);
	cell.cubei.resize(36);
	cell.cubej.resize(36);
	cell.cubek.resize(36);
	for (int f = 0; f < 36; f++)
	{
		cell.labels[f] = -1;
		cell.colorIndices[f] = 0;
		cell.z[f] = -INT_MAX;
		cell.cubei[f] = -INT_MAX;
		cell.cubej[f] = -INT_MAX;
		cell.cubek[f] = -INT_MAX;
	}
}

WB_IsoGridCell::WB_IsoGridCell()
{
	initCell();
}
int WB_IsoGridCell::getLabel(int f)
{
	return labels[f];
}

int WB_IsoGridCell::getColorIndex(int f)
{
	return colorIndices[f];
}

int WB_IsoGridCell::getZ(int f)
{
	return z[f];
}

vec<int> WB_IsoGridCell::getCube(int f)
{
	if (cubei[f] == -INT_MAX)
		return {};
	return { cubei[f], cubej[f], cubek[f] };
}

int WB_IsoGridCell::getQ()
{
	return q;
}

int WB_IsoGridCell::getR()
{
	return r;
}

boolean WB_IsoGridCell::isEmpty()
{
	for (int f = 0; f < 36; f++)
	{
		if (labels[f] > -1)
			return false;
	}
	return true;
}
