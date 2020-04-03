#pragma once
#include "typedef.h"

struct WB_IsoGridCell
{

	int q = 0, r = 0;
	vec<int> z;
	vec<int> labels;
	vec<int> colorIndices;
	vec<int> cubei;
	vec<int> cubej;
	vec<int> cubek;
	
	WB_IsoGridCell();
	void initCell();

	int getLabel(int f);
	int getColorIndex(int f);
	int getZ(int f);
	vec<int> getCube(int f);
	int getQ();
	int getR();
	boolean isEmpty();

	// static  class HexCellSort implements Comparator<WB_IsoGridCell> {
	// 	@Override
	// 	public int compare(WB_IsoGridCell arg0, WB_IsoGridCell arg1) {
	// 		if (arg0.q < arg1.q) {
	// 			return -1;
	// 		} else if (arg0.q > arg1.q) {
	// 			return 1;
	// 		} else if (arg0.r < arg1.r) {
	// 			return -1;
	// 		} else if (arg0.r > arg1.r) {
	// 			return 1;
	// 		}
	// 		return 0;
	// 	}
	// }
};
