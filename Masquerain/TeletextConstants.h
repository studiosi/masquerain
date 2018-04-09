#pragma once

using namespace cv;

namespace Masquerain {

	// Allowed colors in RGB format
	const Vec3b TTX_BLACK(0, 0, 0);
	const Vec3b TTX_RED(255, 0, 0);
	const Vec3b TTX_GREEN(0, 255, 0);
	const Vec3b TTX_BLUE(0, 0, 255);
	const Vec3b TTX_YELLOW(255, 255, 0);
	const Vec3b TTX_MAGENTA(255, 0, 255);
	const Vec3b TTX_CYAN(0, 255, 255);
	const Vec3b TTX_WHITE(255, 255, 255);

	// Array with all the colors in order, for easier processing
	const Vec3b WSTL1_COLORS[8] = { 
		TTX_BLACK, TTX_RED, TTX_GREEN, TTX_BLUE,
		TTX_YELLOW, TTX_MAGENTA, TTX_CYAN, TTX_WHITE 
	};

	const int TTX_COLS = 40;
	const int TTX_ROWS = 25;

}
