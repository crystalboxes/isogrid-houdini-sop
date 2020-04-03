#pragma once

#include "typedef.h"

struct WB_IsoGridSegment
{
	int type = 0; // 0=q, 1=r, 2=-q+r, 3=q+r, 4=q-2r, 5=-2q+r
	int lineValue = 0;
	int sortValue;
	int q1 = 0, r1 = 0, q2 = 0, r2 = 0;

	WB_IsoGridSegment();
	void initialize(int q1, int r1, int q2, int r2);

	int getType() const
	{
		return type;
	}

	int getLineValue() const
	{
		return lineValue;
	}

	int getSortValue() const
	{
		return sortValue;
	}

	int getQ1() const
	{
		return q1;
	}

	int getR1() const
	{
		return r1;
	}

	int getQ2() const
	{
		return q2;
	}

	int getR2() const
	{
		return r2;
	}

	void setQ1(int q1) 
	{
		this->q1 = q1;
	}

	void setR1(int r1)
	{
		this->r1 = r1;
	}

	void setQ2(int q2)
	{
		this->q2 = q2;
	}

	void setR2(int r2)
	{
		this->r2 = r2;
	}

	long getHash() const
	{
		long A = (type >= 0 ? 2 * (long)type : -2 * (long)type - 1);
		long B = (lineValue >= 0 ? 2 * (long)lineValue : -2 * (long)lineValue - 1);
		long C = ((A >= B ? A * A + A + B : A + B * B) / 2);
		return type < 0 && lineValue < 0 || type >= 0 && lineValue >= 0 ? C : -C - 1;
	}

		// static class HexSegmentSort implements Comparator<WB_IsoGridSegment>{
	// 	@Override
	// 	public int compare(WB_IsoGridSegment arg0, WB_IsoGridSegment arg1) {
	// 		return Double.compare(arg0.getSortValue(), arg1.getSortValue());
	// 	}
	// }
};
