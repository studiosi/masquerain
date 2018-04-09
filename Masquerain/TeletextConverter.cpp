#include "stdafx.h"
#include "TeletextConverter.h"

void Masquerain::TeletextConverter::PixelColorChange(Mat * img)
{
	for (int y = 0; y < img->rows; y++) {
		for (int x = 0; x < img->cols; x++) {
			Vec3b currentPixelRGB = img->at<Vec3b>(y, x);
			Vec3b selectedColor;
			double currentMinDistance = DBL_MAX;
			for each (Vec3b color in WSTL1_COLORS)
			{
				double currentDistance = ColorUtils::EuclideanRGBApproximatedPerceivedDistance(currentPixelRGB, color);
				if (currentDistance < currentMinDistance)
				{
					currentMinDistance = currentDistance;
					selectedColor = color;
				}
			}
			img->at<Vec3b>(y, x) = selectedColor;
		}
	}
}

Size Masquerain::TeletextConverter::CalculateCellSize(Mat * img)
{
	int sizeX = img->rows / (TTX_ROWS - 1); // First row is reserved
	int sizeY = img->cols / TTX_COLS;
	// The cells must follow the proportion 2:3
	while ((sizeX % 2) != 0)
	{
		sizeX += 1;
	}
	while (((sizeY % 3) != 0) || (sizeY < sizeX))
	{
		sizeY += 1;
	}
	return Size(sizeX, sizeY);
}

void Masquerain::TeletextConverter::PaintCell(Mat * img, int cellX, int cellY, Size cellSize, Cell cell)
{
	for (int i = 0; i < 6; i++) {
		PaintSubcell(img, cellX, cellY, cellSize, cell, i);
	}
}

void Masquerain::TeletextConverter::PaintSubcell(Mat * img, int cellX, int cellY, Size cellSize, Cell cell, int nSubCell)
{
	bool isForeground = (cell.character[nSubCell] == 1) ? true : false;
	int initX = cellX * cellSize.width;
	int initY = cellY * cellSize.height;
	// InitX Manipulation for the subcell
	if (nSubCell % 2 == 1) {
		initX += cellSize.width / 2;
	}
	// InitY Manipulation for the subcell
	if (nSubCell == 2 || nSubCell == 3) {
		initY += cellSize.height / 3;
	}
	else if (nSubCell == 4 || nSubCell == 5) {
		initY += (cellSize.height / 3) * 2;
	}
	// Painting
	for (int xInc = 0; xInc < cellSize.width / 2; xInc++) {
		for (int yInc = 0; yInc < cellSize.height / 3; yInc++) {
			if (isForeground) {
				img->at<Vec3b>(initY + yInc, initX + xInc) = cell.foregroundColor;
			}
			else {
				img->at<Vec3b>(initY + yInc, initX + xInc) = cell.backgroundColor;
			}
		}
	}
}

Cell Masquerain::TeletextConverter::SelectCell(Mat * img, int cellX, int cellY, Size cellSize)
{
	Cell cell;

	int initX = cellX * cellSize.width;
	int initY = cellY * cellSize.height;

	unordered_map<Vec3b, long, Vec3bHasher> colorMap;

	// colorMap initialization
	for (int i = 0; i < 8; i++) {
		colorMap[WSTL1_COLORS[i]] = 0;
	}

	for (int xInc = 0; xInc < cellSize.width; xInc++) {
		for (int yInc = 0; yInc < cellSize.height; yInc++) {
			if (((initY + yInc) < img->rows) && ((initX + xInc) < img->cols)) {
				cv::Vec3b currentColor = img->at<cv::Vec3b>(initY + yInc, initX + xInc);
				colorMap[currentColor]++;
			}
		}
	}

	cell.foregroundColor = ColorMap::GetColorIndex(colorMap, 0);
	cell.backgroundColor = ColorMap::GetColorIndex(colorMap, 1);

	// Get colorMap for a subcell, then get the maximum color and check 
	// if it is closer to the foreground or the background color, then
	// mark the subcell as 1 or 0 in the character

	std::array<unsigned char, 6> alphamosaic;

	for (int i = 0; i < 6; i++) {
		std::unordered_map<cv::Vec3b, long, Vec3bHasher> subcellColorMap = GetSubcellColorMap(img, cellX, cellY, cellSize, i);
		cv::Vec3b mostCommonColor = ColorMap::GetColorIndex(subcellColorMap, 0);
		alphamosaic[i] = ColorUtils::CloserColor(mostCommonColor, cell.foregroundColor, cell.backgroundColor);
	}

	cell.character = alphamosaic;

	return cell;
}

unordered_map<Vec3b, long, Vec3bHasher> Masquerain::TeletextConverter::GetSubcellColorMap(Mat * img, int cellX, int cellY, Size cellSize, int nSubCell)
{
	unordered_map<Vec3b, long, Vec3bHasher> result;
	int initX = cellX * cellSize.width;
	int initY = cellY * cellSize.height;
	// InitX Manipulation for the subcell
	if (nSubCell % 2 == 1) {
		initX += cellSize.width / 2;
	}
	// InitY Manipulation for the subcell
	if (nSubCell == 2 || nSubCell == 3) {
		initY += cellSize.height / 3;
	}
	else if (nSubCell == 4 || nSubCell == 5) {
		initY += (cellSize.height / 3) * 2;
	}
	// Map initialization
	for (int i = 0; i < 8; i++) {
		result[WSTL1_COLORS[i]] = 0;
	}
	// Painting
	for (int xInc = 0; xInc < cellSize.width / 2; xInc++) {
		for (int yInc = 0; yInc < cellSize.height / 3; yInc++) {
			Vec3b currentColor = img->at<Vec3b>(initY + yInc, initX + xInc);
			result[currentColor]++;
		}
	}
	return result;
}

Mat * Masquerain::TeletextConverter::ConvertSinglePage(Mat * img)
{
	// Change colors
	Mat colorChangedImage = img->clone();
	PixelColorChange(&colorChangedImage);
	// Calculate the cell size
	Size cellSize = CalculateCellSize(&colorChangedImage);
	// Create the converted image
	Mat *convertedImage = new cv::Mat(cellSize.height * TTX_ROWS, cellSize.width * TTX_COLS, img->type());
	// Resize the original image
	resize(colorChangedImage, colorChangedImage, convertedImage->size(), 0.0, 0.0, CV_INTER_NN);
	for (int y = 0; y < TTX_ROWS; y++) {
		for (int x = 0; x < TTX_COLS; x++) {
			Cell currentCell = SelectCell(&colorChangedImage, x, y, cellSize);
			PaintCell(convertedImage, x, y, cellSize, currentCell);
		}
	}
	return convertedImage;
}

