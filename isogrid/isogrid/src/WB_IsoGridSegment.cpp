#include "WB_IsoGridSegment.h"
#include <exception>

WB_IsoGridSegment::WB_IsoGridSegment(){}
void WB_IsoGridSegment::initialize(int q1, int r1, int q2, int r2)
{
	this->q1 = q1;
	this->r1 = r1;
	this->q2 = q2;
	this->r2 = r2;
	type = -1;
	if (q1 == q2)
	{
		type = 0;
		lineValue = q1;
		this->r1 = std::min(r1, r2);
		this->r2 = std::max(r1, r2);
		sortValue = this->r1;
	}
	else if (r1 == r2)
	{
		type = 1;
		lineValue = r1;
		this->q1 = std::min(q1, q2);
		this->q2 = std::max(q1, q2);
		sortValue = this->q1;
	}
	else if (-q1 + r1 == -q2 + r2)
	{
		type = 2;
		lineValue = -q1 + r1;
		if (q1 > q2)
		{
			this->q2 = q1;
			this->q1 = q2;
			this->r2 = r1;
			this->r1 = r2;
		}
		sortValue = this->q1;
	}
	else if (q1 + r1 == q2 + r2)
	{
		type = 3;
		lineValue = q1 + r1;
		if (r1 > r2)
		{
			this->r2 = r1;
			this->r1 = r2;
			this->q2 = q1;
			this->q1 = q2;
		}
		sortValue = this->r1;
	}
	else if (q1 - 2 * r1 == q2 - 2 * r2)
	{
		type = 4;
		lineValue = q1 - 2 * r1;
		if (r1 > r2)
		{
			this->r2 = r1;
			this->r1 = r2;
			this->q2 = q1;
			this->q1 = q2;
		}
		sortValue = this->r1;
	}
	else if (-2 * q1 + r1 == -2 * q2 + r2)
	{
		type = 5;
		lineValue = -2 * q1 + r1;
		if (q1 > q2)
		{
			this->q2 = q1;
			this->q1 = q2;
			this->r2 = r1;
			this->r1 = r2;
		}
		sortValue = this->q1;
	}
	
	if (type == -1)
	{
		auto s = (std::string("Invalid segment: ") + std::to_string(q1) + ", " + std::to_string(r1) + ", " +
		          std::to_string(q2) + ", " + std::to_string(r2) + ".");
		throw std::exception(s.c_str());
	}
}
