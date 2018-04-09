#include "stdafx.h"
#include "ColorMapUtils.h"

Vec3b Masquerain::ColorMap::GetColorIndex(unordered_map<Vec3b, long, Vec3bHasher> colorMap, int index)
{
	vector<long> colorMapValues = GetAllColorMapValues(colorMap);
	sort(colorMapValues.begin(), colorMapValues.end());
	reverse(colorMapValues.begin(), colorMapValues.end());
	long value = colorMapValues[index]; // If badly called, will throw exception
	for (auto it = colorMap.begin(); it != colorMap.end(); it++) {
		if (it->second == value) {
			return it->first;
		}
	}
	// If not found, throw exception
	throw invalid_argument("No color found for that index");
}

vector<long> Masquerain::ColorMap::GetAllColorMapValues(unordered_map<Vec3b, long, Vec3bHasher> colorMap)
{
	// Get all map values
	vector<long> colorMapValues;
	for (auto it = colorMap.begin(); it != colorMap.end(); it++) {
		colorMapValues.push_back(it->second);
	}
	return colorMapValues;
}
