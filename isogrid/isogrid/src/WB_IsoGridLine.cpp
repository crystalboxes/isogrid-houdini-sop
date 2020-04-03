#include "WB_IsoGridLine.h"
#include "WB_IsoGridSegment.h"

void WB_IsoGridLine::add(const WB_IsoGridSegment &segment)
{
	if (segment.getType() == type && segment.getLineValue() == lineValue)
	{
		segments.push_back(segment);
	}
	else
	{
		auto s = (std::string("Segment is type ") + std::to_string(segment.getType()) + " with value " +
		          std::to_string(segment.getLineValue()) + ", and cannot be added to line of type " +
		          std::to_string(type) + " with value " + std::to_string(lineValue) + ".");

		throw std::exception(s.c_str());
	}
}

void WB_IsoGridLine::sort()
{
	std::sort(segments.begin(), segments.end(),
	          [](const WB_IsoGridSegment &a, const WB_IsoGridSegment &b) { return a.getSortValue() < b.getSortValue(); });
}
void WB_IsoGridLine::reverse()
{
	std::reverse(segments.begin(), segments.end());
	for (auto &segment : segments)
	{
		int tmp = segment.getQ2();
		segment.setQ2(segment.getQ1());
		segment.setQ1(tmp);
		tmp = segment.getR2();
		segment.setR2(segment.getR1());
		segment.setR1(tmp);
	}
}

void WB_IsoGridLine::optimize()
{
	vec<WB_IsoGridSegment> newSegments;
	WB_IsoGridSegment *segi;
	WB_IsoGridSegment *segj;
	for (int i = 0; i < segments.size();)
	{
		segi = &segments[i];
		int j = 0;
		for (j = i + 1; j < segments.size(); j++)
		{
			segj = &segments[j];
			if (segj->getQ1() == segi->getQ2() && segj->getR1() == segi->getR2())
			{
				segi->setQ2(segj->getQ2());
				segi->setR2(segj->getR2());
			}
			else
			{
				break;
			}
		}
		i = j;
		newSegments.push_back(*segi);
	}
	segments = newSegments;
}
