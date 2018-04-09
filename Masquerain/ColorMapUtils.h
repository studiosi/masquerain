#pragma once

using namespace cv;
using namespace std;

namespace Masquerain {

	struct Vec3bHasher {
		size_t operator()(const Vec3b &k) const {
			return	(hash<uchar>()(k[0])
					^ ((hash<uchar>()(k[1]) << 1) >> 1)
					^ (hash<uchar>()(k[2]) << 1));
		}
	};

	class ColorMap {
		
	public:

		static Vec3b GetColorIndex(unordered_map<Vec3b, long, Vec3bHasher> colorMap, int index);
		static vector<long> GetAllColorMapValues(unordered_map<Vec3b, long, Vec3bHasher> colorMap);

	};

}
