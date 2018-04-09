#pragma once

#include "TeletextConstants.h"
#include "ColorUtils.h"
#include "ColorMapUtils.h"

using namespace cv;
using namespace std;
using namespace Masquerain;

namespace Masquerain {

	typedef struct Cell {

		Vec3b foregroundColor;
		Vec3b backgroundColor;
		array<unsigned char, 6> character;

	} Cell;

	class TeletextConverter {

	private:

		static void PixelColorChange(cv::Mat *img);
		static Size CalculateCellSize(cv::Mat *img);
		static void PaintCell(Mat *img, int cellX, int cellY, Size cellSize, Cell cell);
		static void PaintSubcell(Mat *img, int cellX, int cellY, Size cellSize, Cell cell, int nSubCell);
		static Cell SelectCell(Mat *img, int cellX, int cellY, Size cellSize);
		static unordered_map<Vec3b, long, Vec3bHasher> GetSubcellColorMap(Mat *img, int cellX, int cellY, Size cellSize, int nSubCell);

	public:

		static Mat *ConvertSinglePage(Mat *img);

	};

}
