#include "stdafx.h"
#include "ColorUtils.h"

double Masquerain::ColorUtils::EuclideanRGBApproximatedPerceivedDistance(Vec3b c1, Vec3b c2)
{
	double r;
	r = 2 * abs(((double)c2.val[0]) - c1.val[0]);	// R
	r += 4 * abs(((double)c2.val[1]) - c1.val[1]);	// G
	r += 3 * abs(((double)c2.val[2]) - c1.val[2]);	// B
	return sqrt(r);
}

unsigned char Masquerain::ColorUtils::CloserColor(Vec3b originalColor, Vec3b foregroundColor, Vec3b backgroundColor)
{
	double d1 = EuclideanRGBApproximatedPerceivedDistance(originalColor, foregroundColor);
	double d2 = EuclideanRGBApproximatedPerceivedDistance(originalColor, backgroundColor);
	if (d1 < d2) {
		return 1;
	}
	else {
		return 0;
	}
}
