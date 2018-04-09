#pragma once

using namespace cv;

namespace Masquerain {


	class ColorUtils {

	public:

		// See https://en.wikipedia.org/wiki/Color_difference 

		static double EuclideanRGBApproximatedPerceivedDistance(Vec3b c1, Vec3b c2);
		static unsigned char CloserColor(Vec3b originalColor, Vec3b foregroundColor, Vec3b backgroundColor);

	};

}