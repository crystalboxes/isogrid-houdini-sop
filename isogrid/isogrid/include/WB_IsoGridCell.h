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
};
