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
    Mat image = imread(input_image);
    if (!image.data) {
        printf("No image data \n");
        return -1;
    }
    string name = input_image.substr(0, input_image.find('.', 0));

    // Create vector of output sizes
    vector<int> sizes = {20, 29, 40, 58, 60, 76, 80, 87, 120, 152, 167, 180, 1024};

    // For each size, write the corresponding image file
    Mat output;
    for (auto size : sizes) {
        if (size < image.rows) {
            resize(image, output, Size(size, size), 0, 0, INTER_AREA);
        } else {
            resize(image, output, Size(size, size), 0, 0, INTER_CUBIC);
        }
        imwrite(name + "-" + to_string(size) + ".png", output);
    }

    return 0;
}
