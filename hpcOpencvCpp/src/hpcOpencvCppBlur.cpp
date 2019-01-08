#include <opencv2/opencv.hpp>
#include <chrono>
#include <iostream>
#include <string>

using timePoint_t = std::chrono::time_point<std::chrono::system_clock>;

auto now = std::chrono::system_clock::now;

double duration(const timePoint_t & tp0, const timePoint_t & tp1) {
    std::chrono::duration<double> nbSeconds = tp1 - tp0;
    return nbSeconds.count();
}

int main(int argc, char ** argv) { 

    // arguments
    if (argc != 5) {
        std::cerr << "usage: " << argv[0] << " <filename> <outfile> <filtersize> <nbruns>";
        exit(-1);
    }
    const std::string FILENAME = argv[1];
    const std::string OUTFILE = argv[2];
    const int FILTERSIZE = atoi(argv[3]);
    const int NBRUNS = atoi(argv[4]);

    // load input image
    cv::Mat imgInput = cv::imread(FILENAME);
    if (imgInput.channels()!=3 or imgInput.depth()!=CV_8U) {
        std::cerr << "error: only 3-channel 8-bits images are supported\n";
        exit(-1);
    }

    timePoint_t tp0 = now();

    // blur
    cv::Mat imgBlur = imgInput.clone();
    for (int k=0; k<NBRUNS; k++) {
        blur(imgInput, imgBlur, cv::Size(FILTERSIZE, FILTERSIZE));
    }

    timePoint_t tp1 = now();

    // outputs
    std::cout << "time: " << duration(tp0, tp1) << " s\n";
    imwrite(OUTFILE, imgBlur);

    return 0;
}
