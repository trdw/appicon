#include <opencv2/opencv.hpp>
#include <string>
using namespace cv;
using namespace std;

int main(const int argc, const char * argv[]) {
    const std::string keys =
            "{help h usage ?      |          | print this message                      }"
            "{@input_image        |<none>    | input image                             }";
    // Parse arguments
    CommandLineParser parser(argc, argv, keys);
    parser.about("Appicon generator (image resizer)");
    if (parser.has("help")) {
        parser.printMessage();
        return 0;
    }
    string input_image = parser.get<string>("@input_image");
    if (!parser.check()) {
        parser.printErrors();
        parser.printMessage();
        return -1;
    }

    // Read the input image file
    Mat image = imread(input_image, IMREAD_GRAYSCALE);
    if (!image.data) {
        printf("No image data \n");
        return -1;
    }

    // Create vector of output sizes
    vector<int> sizes = {20, 29, 40, 58, 76, 80, 87, 120, 152, 167, 180};

    // For each size, write the corresponding image file
    Mat output;
    for (auto size : sizes) {
        resize(image, output, Size(size, size));
        imwrite(to_string(size) + ".png", output);
    }

    return 0;
}
