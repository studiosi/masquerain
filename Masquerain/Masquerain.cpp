#include "stdafx.h"

#include "TeletextConverter.h"

using namespace std;
using namespace boost::program_options;
using namespace cv;

bool checkValues(variables_map * takenOptions) {
	bool inputOK = takenOptions->count("input") > 0;
	bool outputOK = takenOptions->count("output") > 0;
	if (!(inputOK && outputOK)) {
		return false;
	}
	return true;       
}

int main(int argc, char *argv[])
{
	//
	// Options
	//
	// -i --input (required): input file
	// -o --output (required): output file
	// -h --help: show usage
	//

	options_description options("Options");
	options.add_options()
		("help,h", "Shows Usage")
		("input,i", value<string>(), "Input File")
		("output,o", value<string>(), "Output File");

	variables_map takenOptions;
	store(parse_command_line(argc, argv, options), takenOptions);
	notify(takenOptions);

	// Help is an option that overrides the rest
	if (takenOptions.count("help") > 0) {		
		cout << options << endl;
		return EXIT_SUCCESS;
	}

	// Both input and output must be specified
	if (!checkValues(&takenOptions)) {
		cout << "Both input and output must be specified." << endl;
		cout << options << endl;
		return EXIT_FAILURE;
	}

	// If both are OK, then we proceed
	string inputPath = takenOptions["input"].as<string>();
	string outputPath = takenOptions["output"].as<string>();

	cout << "INPUT FILE: " << inputPath << endl;
	cout << "OUTPUT FILE: " << outputPath << endl;

	Mat image = imread(inputPath);
	if (image.data == NULL) {
		cout << "Error reading input image." << endl;
		return EXIT_FAILURE;
	}

	Mat *output = TeletextConverter::ConvertSinglePage(&image);

	if (!imwrite(outputPath, *output)) {
		cout << "Error saving output image." << endl;
		return EXIT_FAILURE;
	}

	delete output;
    return EXIT_SUCCESS;
}

