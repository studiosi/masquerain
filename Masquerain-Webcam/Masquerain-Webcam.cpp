#include "stdafx.h"

using namespace std;
using namespace cv;

const int MAX_FAILURES = 20;

int main()
{
	VideoCapture cap(0);

	if (!cap.isOpened()) {
		cout << "No video capture device found!" << endl;
		return EXIT_FAILURE;
	}

	int failures = 1;
	for (;;) {
		Mat frame;
		if (!cap.retrieve(frame)) {
			cout << "Error retrieving frame!" << endl;
			failures++;
			if (failures == MAX_FAILURES) {
				cout << "Max failures reached";
				return EXIT_FAILURE;
			}
			continue;
		}
		Mat * convertedFrame = TeletextConverter::ConvertSinglePage(&frame);
		imshow("", *convertedFrame);
		int key = waitKey(1);
		if (key == 'q') {
			delete convertedFrame;
			cout << "Exiting..." << endl;
			return EXIT_SUCCESS;
		}
		delete convertedFrame;
	}

    return EXIT_SUCCESS;
}

