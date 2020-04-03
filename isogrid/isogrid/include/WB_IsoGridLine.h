#pragma once
#include "WB_IsoGridSegment.h"
#include "typedef.h"

struct WB_IsoGridLine
{
  int type = 0; // 0=q, 1=r, 2=-q+r, 3=q+r, 4=q-2r, 5=-2q+r
  int lineValue = 0;
  vec<WB_IsoGridSegment> segments;

  WB_IsoGridLine()
  {
    segments.clear();
  }
  WB_IsoGridLine(int type, int value)
  {
    this->type = type;
    this->lineValue = value;
    segments.clear();
  }

  void add(const WB_IsoGridSegment &segment);

  void sort();

  void reverse();
  void optimize();

  int getType()
  {
    return type;
  }

  int getLineValue()
  {
    return lineValue;
  }

  vec<WB_IsoGridSegment> *getSegments()
  {
    return &segments;
  }

  long getHash()
  {
    long A = (type >= 0 ? 2 * (long)type : -2 * (long)type - 1);
    long B = (lineValue >= 0 ? 2 * (long)lineValue : -2 * (long)lineValue - 1);
    long C = ((A >= B ? A * A + A + B : A + B * B) / 2);
    return type < 0 && lineValue < 0 || type >= 0 && lineValue >= 0 ? C : -C - 1;
  }
};
